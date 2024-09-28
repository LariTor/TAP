import heapq


def max_beast_health(N, P, weapons):
    # Priority queue: each state is (-damage, current_power, used weapons as a tuple)
    pq = [(-0, P, tuple())]  # Start with full power and 0 damage
    max_damage = 0

    # Visited dictionary to track the (power points, tuple of used weapons) states
    visited = {}
    visited[(P, tuple())] = 0  # Track the maximum damage for each state

    # Function to calculate an adaptive upper bound on remaining damage
    def remaining_damage_upper_bound(remaining_weapons, current_power):
        remaining_damage = 0
        sorted_weapons = sorted(
            remaining_weapons, key=lambda w: (w[2], w[1]), reverse=True)
        current_power *= 1.5

        for A, B, C in sorted_weapons:
            if current_power >= B:
                new_power = (current_power - B) // A
                remaining_damage += C
                current_power = new_power
            if current_power <= 0:
                break
        return remaining_damage

    while pq:
        # Get the state with the maximum potential damage
        neg_damage, power, used_weapons = heapq.heappop(pq)
        damage = -neg_damage

        # Update the maximum damage
        max_damage = max(max_damage, damage)

        # Compute the remaining potential damage considering only unused weapons
        remaining_weapons = [weapons[i]
                             for i in range(N) if i not in used_weapons]
        potential_remaining_damage = remaining_damage_upper_bound(
            remaining_weapons, power)

        # Prune the branch if it cannot exceed the maximum damage found so far
        if damage + potential_remaining_damage <= max_damage:
            continue

        # Try using each weapon, skipping already used ones
        used_set = set(used_weapons)

        for i in range(N):
            if i in used_set:
                continue  # Skip already used weapons

            A, B, C = weapons[i]
            if power >= B:
                # Calculate new power and damage after using weapon i
                new_power = (power - B) // A
                new_damage = damage + C
                new_used_weapons = used_weapons + (i,)

                # If new state can improve, push it into the queue
                if new_power >= 0 and new_damage > visited.get((new_power, new_used_weapons), -float('inf')):
                    visited[(new_power, new_used_weapons)] = new_damage
                    heapq.heappush(
                        pq, (-new_damage, new_power, new_used_weapons))

    return max_damage


# Input example
N, P = map(int, input().split())
weapons = [tuple(map(int, input().split())) for _ in range(N)]

# Output the maximum amount of health points the Beast can have
print(max_beast_health(N, P, weapons))
