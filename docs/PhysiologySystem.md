# Physiology System

## Design Philosophy

**1. Potential Physiology State Attributes**

These represent the AI's physical condition and bodily needs/states.

* **Health (HP):** Current level of physical integrity, damage sustained (e.g., 0-100).
* **Stamina / Endurance:** Capacity for short-term exertion like sprinting, heavy attacks (e.g., 0-100, drains and recovers).
* **Hunger:** Level of satiation, need for food (e.g., 0-100, 100=full, degrades over time).
* **Thirst:** Level of hydration (similar to Hunger).
* **Body Temperature:** Core body temperature, relevant in survival contexts (e.g., degrees, with optimal/dangerous ranges).
* **Pain Level:** Intensity of current physical pain sensation, separate from HP (e.g., 0-10, high levels impair function).
* **Blood Loss:** Status indicating ongoing bleeding, potentially affecting other stats (e.g., boolean or rate).
* **Oxygen Level:** Air supply, relevant underwater or in toxic zones (e.g., 0-100, depletes).
* **Poison/Disease Status:** Type and severity of afflictions affecting the body.
* **Adrenaline Level:** Temporary physiological boost triggered by stress/threat (e.g., 0-100 or timer-based effect).
* **Rest Level / Sleepiness:** Need for sleep or rest (e.g., 0-100, 100=fully rested).

**2. Relationships Between Physiology, Emotions, and Mental States**

This creates a complex web of interactions:

* **Physiology -> Emotions:**
    * *Negative States Trigger Negative Emotions:* Low Health, High Pain, Hunger, Thirst, Suffocation strongly increase *Fear*, *Anger* (irritability), *Sadness* (discomfort). Poison/Disease triggers *Fear*, *Disgust*.
    * *Adrenaline Interaction:* High Adrenaline often correlates with intense *Fear* or *Anger*, potentially suppressing other feelings temporarily.
    * *Mechanism:* Physiological states directly influence the emotional response to events (input mapping) or can generate internal emotional stimuli.

* **Physiology -> Mental States:**
    * *Negative States Degrade Mental Function:* Low Health, High Pain, Hunger, Thirst, Lack of Sleep severely increase *Stress Level* and *Fatigue*, decrease *Focus*, *Morale*, and potentially *Sanity* (especially chronic conditions).
    * *Temperature Effects:* Extreme cold/heat increases *Stress* and decreases *Focus*.
    * *Adrenaline Effects:* High Adrenaline can temporarily boost *Alertness* and *Focus* (tunnel vision) but often leads to a subsequent crash increasing *Fatigue*.
    * *Mechanism:* Physiological sensor readings directly modify Mental State values, often checked periodically.

* **Emotions -> Physiology:**
    * *Stress Response:* Intense *Fear* or *Anger* can trigger an *Adrenaline* surge.
    * * psychosomatic Effects (Advanced):* Chronic high *Fear* or *Stress* (mental state influenced by emotions) could potentially degrade *Health* slightly over long periods or influence recovery rates (e.g., slower stamina regen when highly stressed/afraid). Joy/Contentment might slightly aid recovery during rest.
    * *Mechanism:* Specific emotional states (especially high intensity) can trigger changes in physiological attributes like Adrenaline.

* **Emotions -> Mental States:** (As discussed previously)
    * Chronic high *Fear*/*Disgust* erodes *Sanity*, *Morale*. Chronic *Sadness* lowers *Morale*, increases *Fatigue*. High *Stress* amplifies negative emotions.

* **Mental States -> Physiology:**
    * *Stress/Sanity Impact:* High *Stress Level* or low *Sanity* could manifest physiologically over time (e.g., increased *Fatigue*, maybe minor *Health* impact, suppressed *Hunger* cues, neglecting needs leading to worse Hunger/Thirst/Rest).
    * *Morale/Focus Impact:* Low *Morale* might lead to physical sluggishness (affecting stamina use/recovery indirectly). High *Focus* might allow ignoring minor *Pain*.
    * *Mechanism:* Mental states can influence the rate of change of physiological needs or trigger behaviors that impact physiology.

* **Mental States -> Emotions:** (As discussed previously)
    * Low *Sanity*/*Morale* amplifies *Fear*. High *Stress* amplifies *Fear*/*Anger*. *Confidence* dampens *Fear*.

* **Game Events -> Affect All Three:**
    * *Getting shot:* `-Health`, `+Pain` (Physiology); `+Fear`, `+Anger` (Emotion); `+Stress`, `-Focus` (Mental State).
    * *Running from danger:* `-Stamina` (Physiology); *Fear* sustained/increased (Emotion); `+Stress`, `-Focus` potentially (Mental State).

**Summary of Interactions:**

| System        | Affects Emotions?              | Affects Mental States?          | Affects Physiology?               |
| :------------ | :----------------------------- | :------------------------------ | :-------------------------------- |
| **Physiology** | Yes (Pain->Fear, Hunger->Anger) | Yes (Low HP->Stress/Morale)    | ---                               |
| **Emotions** | ---                            | Yes (Chronic Fear->Sanity/Morale) | Yes (Fear->Adrenaline, +/-Recovery) |
| **Mental State**| Yes (Low Morale->Fear Amp)   | ---                             | Yes (Stress->Fatigue, Sanity->Neglect)|

**3. Architecture Design Exploration (with 3 Systems)**

Extending the previous designs:

**A. Layered / Separate Systems:**

```
+---------------------+      +-------------------------+
| GameWorldInterface  |----->|  AIController / Brain   |
+---------------------+      +-------+-----------+-----+
                                     |           |
                                     v           v Process Events & State
                          +-----------------------+
                          | InputProcessor/Mapper |
                          +-----------+-----------+
                               |      |      |
            Direct Update      v      v      v      Output Read by Behavior
+------------------+<----->+---------------+<----->+--------------------+
| PhysiologySystem |------>| EmotionSystem |------>| MentalStateSystem  |
|(HP, Stamina...)  |       |(Joy, Fear...) |       |(Sanity, Morale...) |
+------------------+<----->+---------------+<----->+--------------------+
       ^       |                 ^       |                 ^       |
       |-------+-----------------+-------+-----------------+-------| Cross-Influence Logic
                              (Managed by AIController)
```

* **Flow:** Events hit Input Processor, which calculates direct impacts for all 3 systems. AI Controller reads states from all 3, calculates the complex cross-influences (e.g., how current high Fear drains Sanity over time, how low HP amplifies Fear response), and sends updates/modifies mappings.
* **Pros:** Clear separation, modularity.
* **Cons:** Interaction logic within the AI Controller becomes significantly complex, managing a 3x3 matrix of potential influences.

**B. Integrated State Manager:**

```
+---------------------+      +-----------------------------+
| GameWorldInterface  |----->|     AI State Manager        |
+---------------------+      |-----------------------------|
                             | - InputProcessor/Mapper     |
                             | - Emotion Subsystem         |
                             | - Mental State Subsystem    |
                             | - Physiology Subsystem      |
                             | - Cross-Influence Logic     |
                             +-------------+---------------+
                                           |
                                           v Output Read by Behavior
                                     (Behavior Modules)
```

* **Flow:** The single manager handles event mapping and all internal updates, including cross-influences between emotions, mental states, and physiology.
* **Pros:** Potentially simplifies update loops if influences are immediate and tightly coupled.
* **Cons:** Creates a very large, monolithic component. Difficult to maintain, test, or modify subsystems independently. High internal complexity.

**C. Blackboard Architecture:**

```
+---------------------+      +-----------------------+      +----------------------+
| GameWorldInterface  |----->| InputProcessor/Mapper |----->|       Blackboard     |
+---------------------+      +-----------------------+      |----------------------|
                                     ^                      | - Emotion States     |
                                     | Read Context         | - Mental States      |
                                     |                      | - Physiology States  |
+----------------+               +---|----------------+     | - Percepts, Goals... |
| EmotionSystem  |<--------------|   (Other Systems)  |----->| - ...                |
| (Reads/Writes BB)|------------>| (MentalStateSystem,|     +----------^-----------+
+----------------+               | PhysiologySystem,  |                | Read State
                                 | Behavior Modules...) |                |
+----------------+               +--------------------+           (Behavior Modules)
| PhysiologySyst |
| (Reads/Writes BB)|
+----------------+               +--------------------+
| MentalStateSyst|               | InfluenceProcessor |
| (Reads/Writes BB)|               | (e.g., Fear->Sanity)|
+----------------+               +--------------------+
```

* **Flow:** Systems (Emotion, Mental State, Physiology) operate quasi-independently. They read necessary context (including states from other systems) from the Blackboard, calculate their updates based on events/stimuli, and write their results back. Dedicated "Influence Processors" can handle specific complex interactions (like Fear draining Sanity over time) by reading and writing to the Blackboard. Behavior modules read the final state from the Blackboard.
* **Pros:** Maximizes modularity and decoupling. Scalable – easier to add more systems. Handles complex interactions via specialized, focused modules.
* **Cons:** Requires careful design of what reads/writes when. Debugging data flow can be more complex than direct calls. Potential performance overhead (though often manageable).

**Conclusion:**

Introducing a Physiology system significantly increases the complexity of interactions. While a Layered approach is possible, the interaction logic becomes heavy. An Integrated manager risks becoming unwieldy. The **Blackboard architecture** often becomes the most practical solution at this level of complexity, allowing specialized systems to manage their own state while interacting indirectly through shared data, keeping individual components more manageable.

## Creating a Core, Condensed, and Simplified Physiology System 

**Goal:** Represent the AI's essential physical state relevant to performance, emotions, and mental condition, while minimizing complexity.

**Core Condensed Attributes:**

We'll select and combine attributes to cover the most frequent gameplay interactions:

1.  **`Health` (HP):**
    * **Represents:** Physical integrity, damage sustained.
    * **Range:** Typically 0-100 (or max HP). 0 = Dead/Incapacitated.
    * **Purpose:** Standard measure of survivability and damage state. Essential for combat and survival.

2.  **`Stamina` (Endurance):**
    * **Represents:** Short-term capacity for physical exertion (running, heavy attacks, special moves).
    * **Range:** Typically 0-100. Drains with exertion, recovers with rest.
    * **Purpose:** Limits intense actions, provides tactical pacing.

3.  **`Condition` (Vigor / Well-being):**
    * **Represents:** A combined measure of general physical readiness and needs satisfaction. *Abstracts away tracking individual Hunger, Thirst, Rest Level, and minor non-critical Pain/Sickness*.
    * **Range:** 0-100. 100 = Optimal condition (well-fed, rested, hydrated, healthy). Low values indicate neglect, exhaustion, or suffering from minor ailments/pain.
    * **Purpose:** Represents the impact of basic needs and general wellness on performance and mood without detailed tracking. Degrades slowly over time, faster under stress or poor health, restored by specific actions (eating, resting, healing).

4.  **`Adrenaline`:**
    * **Represents:** A temporary physiological fight-or-flight response boost.
    * **Range:** 0-100 (or boolean + timer). Represents the current level of the surge, decaying over time. 0 = Normal state.
    * **Purpose:** Models temporary performance enhancement (speed, power, pain suppression) triggered by threat/intense emotion, often with a subsequent cost (e.g., faster stamina drain or fatigue).

**Simplified Relationships:**

Focus on the most direct and impactful interactions:

* **Physiology -> Emotions:**
    * Low `Health`: Increases Fear, Anger; Suppresses Joy.
    * Low `Stamina` (Exhaustion): Increases Anger (irritability).
    * Low `Condition`: Increases Anger, Sadness (discomfort); Suppresses Joy. Becomes a strong driver if critical.
    * High `Adrenaline`: Amplifies Fear/Anger; may suppress Pain effect temporarily.

* **Physiology -> Mental States:**
    * Low `Health`: Increases Stress; Decreases Focus, Morale, possibly Sanity (if severe/chronic).
    * Low `Stamina` (Exhaustion): Decreases Focus.
    * Low `Condition`: Increases Stress, Fatigue; Decreases Focus, Morale. Significant impact if critical.
    * High `Adrenaline`: Temporarily boosts Alertness/Focus (tunnel vision); subsequent crash increases Fatigue.

* **Emotions -> Physiology:**
    * High Intensity `Fear` / `Anger`: Triggers/Boosts `Adrenaline`.

* **Mental States -> Physiology:**
    * High `Stress` / Low `Sanity`: May accelerate `Condition` degradation (neglect/physiological toll).
    * High `Fatigue`: May slow `Stamina` recovery.

**Conceptual System Interface:**

```python
class SimplifiedPhysiologySystem:
    # Internal state for an AI would include: health, stamina, condition, adrenaline

    # --- Input Methods ---
    def apply_damage(self, ai_id: str, amount: int, damage_type: str = None):
        # Decreases health, potentially triggers pain effect influencing Condition slightly
        pass

    def apply_healing(self, ai_id: str, amount: int):
        # Increases health
        pass

    def consume_stamina(self, ai_id: str, amount: int):
        # Decreases stamina due to exertion
        pass

    def recover_stamina(self, ai_id: str, base_rate: float):
        # Increases stamina, rate might be modified by Condition/Fatigue
        pass

    def degrade_condition(self, ai_id: str, amount: float):
        # Decreases condition due to time, neglect, stress, minor pain/sickness
        pass

    def restore_condition(self, ai_id: str, amount: int, source: str):
        # Increases condition from food, rest, specific care actions
        pass

    def trigger_adrenaline_surge(self, ai_id: str, level: int = 100, decay_rate: float = 5.0):
        # Sets adrenaline level, starts decaying
        pass

    # --- Output Methods ---
    def get_health_percentage(self, ai_id: str) -> float:
        # Returns health as a percentage (0.0 to 1.0)
        pass

    def get_stamina_percentage(self, ai_id: str) -> float:
        # Returns stamina as a percentage (0.0 to 1.0)
        pass

    def get_condition_percentage(self, ai_id: str) -> float:
        # Returns condition as a percentage (0.0 to 1.0)
        pass

    def get_adrenaline_level(self, ai_id: str) -> int:
        # Returns current adrenaline level (0-100)
        pass

    def is_physically_impaired(self, ai_id: str) -> bool:
        # Simple check for critical state
        # return self.get_health_percentage(ai_id) < 0.25 or \
        #        self.get_stamina_percentage(ai_id) < 0.10 or \
        #        self.get_condition_percentage(ai_id) < 0.20
        pass

    def get_overall_physical_modifier(self, ai_id: str) -> float:
        # Provides a single factor (e.g., 0.5 to 1.5) summarizing the current
        # positive/negative impact of physiology on performance/mood.
        # Combines health, stamina, condition effects.
        # Useful for modulating emotional responses or action success chances.
        pass

    # --- Internal Update (called periodically) ---
    def update(self, ai_id: str, delta_time: float):
        # - Decay adrenaline level
        # - Apply slow condition degradation
        # - Apply stamina recovery (if not exerting)
        pass
```

**Architecture Integration:**

This simplified system slots easily into the architectures discussed:

* **Layered:** Fewer states and interactions simplify the logic needed in the `AIController`.
* **Integrated:** The `AIStateManager` incorporates these 4 attributes alongside Emotions and Mental States. Less internal complexity than the full Physiology system.
* **Blackboard:** The `PhysiologySystem` module manages these 4 states, reading/writing them to the `Blackboard`. Other systems read these simpler states.

**Conclusion:**

This condensed Physiology System (`Health`, `Stamina`, `Condition`, `Adrenaline`) provides core physical feedback for AI behavior, emotions, and mental states without the overhead of tracking numerous individual needs unless your specific game design requires that level of detail (e.g., hardcore survival games). It focuses on the states most likely to cause significant changes in AI actions and reactions.