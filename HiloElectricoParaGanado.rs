type CercoI = usize;

static CERCOS: Vec<Cerco> = Vec::new();

#[derive(Debug)]
struct CercoStats {
    m: u32,
    a: f64,
    e: f64,
}

#[derive(Debug)]
struct Cerco {
    x0: i32,
    y0: i32,
    x1: i32,
    y1: i32,
    hijos: Vec<CercoI>,
    padre: Option<CercoI>,
    self_i: CercoI,
    stats: CercoStats,
}

impl Cerco {
    pub fn insertar_cerco(&mut self, cerco: &mut Cerco) {
        cerco.padre = Some(self.self_i);
        self.hijos.push(cerco.self_i);
    }

    pub fn insertar_punto(&mut self) {
        self.stats.m += 1;
    }

    pub fn resolver(&mut self) {
        if self.hijos.is_empty() {
            self.stats.a += 1.0;
            return;
        }
        let hijo = self.merge_fus(0, self.hijos.len() - 1);
        let lm = self.stats.m + hijo.m;
        let la;
        let le;
        if lm == 0 {
            la = 0.0;
            le = 0.0;
        } else {
            let ph = f64::from(hijo.m) / f64::from(lm);
            let pp = f64::from(self.stats.m) / f64::from(lm);
            let phh = ph * ph;
            let php = ph * pp;
            la = hijo.a * ph + self.stats.a * pp + 1.;
            le = hijo.e * phh + 2. * hijo.a * php;
        }
        self.stats.m = lm;
        self.stats.a = la;
        self.stats.e = le;
    }

    pub fn merge_fus(&self, l: usize, r: usize) -> CercoStats {
        if l == r {
            return CERCOS[l].stats;
        }
        let mid = 
    }
}

fn main() {}
