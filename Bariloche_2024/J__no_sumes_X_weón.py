class DoublyLinkedList:
    def __init__(self):
        self.elements = []
        self.links = {}
        self.reverse_links = {}
        self.first_index = None
        self.last_index = None

    def insert(self, value):
        if len(self.elements) == 0:
            self.elements.append(value)
            self.first_index = 0
            self.last_index = 0
        else:
            self.elements.append(value)
            new_index = len(self.elements) - 1
            self.links[self.last_index] = new_index
            self.reverse_links[new_index] = self.last_index
            self.last_index = new_index

    def get_next_index(self, current_index):
        return self.links.get(current_index, None)

    def get_prev_index(self, current_index):
        return self.reverse_links.get(current_index, None)

    def insert_first_at(self, index):
        if self.first_index == index:
            return False

        first_index = self.first_index
        self.first_index = self.get_next_index(self.first_index)

        next_index = self.get_next_index(index)
        self.links[index] = first_index
        self.reverse_links[first_index] = index
        if next_index is not None:
            self.links[first_index] = next_index
            self.reverse_links[next_index] = first_index

        return True

    def insert_last_at(self, index):
        if self.last_index == index:
            return False

        last_index = self.last_index
        prev_last = self.get_prev_index(last_index)
        if prev_last is not None:
            del self.links[prev_last]
        self.last_index = prev_last

        next_index = self.get_next_index(index)
        self.links[index] = last_index
        self.reverse_links[last_index] = index
        if next_index is not None:
            self.links[last_index] = next_index
            self.reverse_links[next_index] = last_index

        return True

    def traverse(self, action):
        current_index = self.first_index
        while current_index is not None:
            action(self.elements[current_index])
            current_index = self.get_next_index(current_index)

    def reverse_traverse(self, action):
        current_index = self.last_index
        while current_index is not None:
            action(self.elements[current_index])
            current_index = self.get_prev_index(current_index)


def solve(N, X, beauties):
    dll = DoublyLinkedList()
    beauties_sorted = sorted(beauties)

    for beauty in beauties_sorted:
        dll.insert(beauty)

    current_index = dll.first_index
    while current_index is not None:
        next_index = dll.get_next_index(current_index)
        if (
            next_index is not None
            and dll.elements[current_index] + dll.elements[next_index] == X
        ):
            valid_operation = True
            if dll.elements[current_index] + dll.elements[dll.last_index] != X:
                dll.insert_last_at(current_index)
            elif dll.elements[dll.first_index] + dll.elements[next_index] != X:
                valid_operation = dll.insert_first_at(current_index)
            else:
                print("*")
                return
            if not valid_operation:
                print("*")
                return

        current_index = dll.get_next_index(current_index)

    dll.traverse(custom_print)


def custom_print(value):
    print(f"{value} ", end="")


N, X = map(int, input().split())
beauties = list(map(int, input().split()))
solve(N, X, beauties)
