import random
import time
from dataclasses import dataclass, field

@dataclass
class Environment:

    temperature: float = field(default_factory=lambda: random.uniform(18, 32))
    light_level: float = field(default_factory=lambda: random.uniform(0, 1000))
    motion_detected: bool = field(default_factory=lambda: random.choice((True, False)))
    hour_of_day: int = field(default_factory=lambda: random.randint(0, 23))

    def step(self):
        self.temperature += random.uniform(-1.5, 1.5)
        self.light_level = max(0, min(1000, self.light_level + random.uniform(-150, 150)))
        self.motion_detected = random.random() < 0.5
        self.hour_of_day = (self.hour_of_day + 1) % 24

    def get_percept(self):
        return {
            "temperature": round(self.temperature, 1),
            "light_level": round(self.light_level, 1),
            "motion_detected": self.motion_detected,
            "hour_of_day": self.hour_of_day,
        }


class SmartHomeAgent:

    def __init__(self):
        self.ac_on = False
        self.heater_on = False
        self.lights_on = False
        self.door_locked = True
        self.log = []

    def perceive_and_act(self, percept: dict) -> list:

        actions = []

        temp = percept["temperature"]
        light = percept["light_level"]
        motion = percept["motion_detected"]
        hour = percept["hour_of_day"]

        is_night = hour < 6 or hour >= 20

        if temp > 26:

            if not self.ac_on:
                self.ac_on = True
                actions.append("AC turned ON (cooling)")

            if self.heater_on:
                self.heater_on = False
                actions.append("Heater turned OFF")

        elif temp < 20:

            if not self.heater_on:
                self.heater_on = True
                actions.append("Heater turned ON")

            if self.ac_on:
                self.ac_on = False
                actions.append("AC turned OFF")

        else:

            if self.ac_on:
                self.ac_on = False
                actions.append("AC turned OFF (comfortable temp)")

            if self.heater_on:
                self.heater_on = False
                actions.append("Heater turned OFF (comfortable temp)")

        if motion and (light < 300 or is_night):

            if not self.lights_on:
                self.lights_on = True
                actions.append("Lights turned ON (occupant present, low light)")

        else:

            if self.lights_on:
                self.lights_on = False
                actions.append("Lights turned OFF (no occupant / bright enough)")

        if not motion and is_night:

            if not self.door_locked:
                self.door_locked = True
                actions.append("Door LOCKED (night, unoccupied)")

        elif motion and not self.door_locked:
            actions.append("Door remains UNLOCKED (occupant active)")

        if not actions:
            actions.append("No action needed (environment already optimal)")

        self.log.append({"percept": percept, "actions": actions})

        return actions


def run_simulation(steps: int = 8, delay: float = 0.0):

    env = Environment()
    agent = SmartHomeAgent()

    print("=" * 70)
    print("SMART HOME CONTROLLER AGENT - SIMULATION START")
    print("=" * 70)

    for t in range(1, steps + 1):

        percept = env.get_percept()
        actions = agent.perceive_and_act(percept)

        print(f"\n--- Time Step {t} (Hour: {percept['hour_of_day']:02d}:00) ---")

        print(
            f"Sensors -> Temp: {percept['temperature']}°C | "
            f"Light: {percept['light_level']} lux | "
            f"Motion: {percept['motion_detected']}"
        )

        print("Actuators:")

        for a in actions:
            print(f"  > {a}")

        print(
            f"State -> AC: {'ON' if agent.ac_on else 'OFF'} | "
            f"Heater: {'ON' if agent.heater_on else 'OFF'} | "
            f"Lights: {'ON' if agent.lights_on else 'OFF'} | "
            f"Door: {'LOCKED' if agent.door_locked else 'UNLOCKED'}"
        )

        env.step()

        if delay:
            time.sleep(delay)

    print("\n" + "=" * 70)
    print("SIMULATION END")
    print("=" * 70)

    return agent.log


if __name__ == "__main__":
    run_simulation(steps=8)