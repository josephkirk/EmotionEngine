# Intent and Goal design to be affect by emotions
## Problem 
"Murderous intent" goes beyond a simple emotion like Anger. It implies a **directed drive, goal, or persistent state** focused on lethally harming a target. Designing it requires thinking about how it arises and how it influences behavior more strongly or persistently than a fleeting feeling.

Here are a few ways to design and integrate such a concept, ranging in complexity:

**1. As an Extreme Emotion Variation (Simplest, Least Accurate)**

* **Design:** Define a state like "Murderous Rage" as the highest intensity variation of "Anger" (e.g., Intensity 95-100). Possibly require a secondary condition, like high "Disgust" (forming Hatred) towards the target as well.
* **Trigger:** Extreme provocation, betrayal by the target when already highly Angry/Disgusted.
* **Effect:** While in this state, AI prioritizes aggressive actions towards the trigger source.
* **Pros:** Easy to integrate into the existing Emotion system.
* **Cons:** Doesn't capture the *intent* well – it's just peak anger. It might fade quickly based on emotion dynamics. Doesn't distinguish between hot-blooded rage and cold, calculated intent. Doesn't explicitly track the *target* of the intent beyond the immediate trigger context.

**2. As a Component of Mental State (More Persistent)**

* **Design:** Introduce a "Hostility" or "Malice" Mental State attribute (0-100). High levels represent a strong negative disposition. "Murderous Intent" could be represented by Hostility > 90 *specifically directed towards a target*. This requires the Mental State system to potentially track target-specific values or have a general level combined with target focus. Could also link to low "Empathy" or "Sanity" states.
* **Trigger:** Chronic high Anger/Disgust towards a target, betrayals, deep-seated grudges (personality), certain sanity breaks. These would increase the Hostility state over time or via specific events.
* **Effect:** High Hostility strongly biases behavior towards negative/harmful actions against relevant targets. Influences dialogue to be threatening, action selection towards aggression.
* **Pros:** More persistent than an emotion variation. Can build up over time. Can be influenced by various factors (emotions, events, personality).
* **Cons:** Still doesn't perfectly model *active intent* or a *plan*. A high Hostility score is a disposition; the AI isn't necessarily *acting* on it *right now* unless other conditions are met. Target tracking can add complexity.

**3. As a Goal/Drive (Most Accurate for "Intent")**

* **Design:** Implement or leverage a Goal-Oriented Action Planning (GOAP) or Behavior Tree system alongside the state systems. "Murderous Intent" is modeled as an active, high-priority **Goal**.
    * **Goal Structure Example:** `Goal{ type: ELIMINATE, target: 'PlayerCharacter', priority: 95, status: ACTIVE }`
* **Trigger:** This goal gets pushed onto the AI's goal stack/priority list when specific conditions involving Emotions, Mental States, Events, and Personality are met.
    * *Examples:*
        * `Emotion.Anger[target] > 90` AND `MentalState.Sanity < 30` AND `Event.Betrayal(source=target)`
        * `Personality.Ruthless=True` AND `Situation.Opportunity=High` AND `Relationship.Enemy(target)`
        * `MentalState.Fear > 80` AND `Perception. inescapableThreat(source=target)` (pre-emptive)
* **Persistence:** The `ELIMINATE` goal remains active (driving behavior) until:
    * Achieved (target eliminated).
    * Invalidated (target escapes definitively, diplomatic resolution occurs).
    * Preempted by a *higher priority* goal (e.g., `SELF_PRESERVE` if the AI is near death and overwhelmed).
* **Effect:** An active `ELIMINATE` goal directly instructs the AI's action selection/planning modules to choose behaviors that progress towards killing the target (e.g., `FindWeapon`, `StalkTarget`, `AmbushTarget`, `AttackTarget`). It overrides lower-priority goals like `PatrolArea` or `TalkToNPC`.
* **Pros:** Accurately models *intent* as a directed objective. Handles persistence, priority, and targeting explicitly. Integrates naturally with AI planning and action selection. Clearly separates feeling (emotion) from doing (goal-driven action).
* **Cons:** Requires a goal management system, adding architectural complexity if one doesn't already exist.

**4. As a Derived "Disposition" State (Hybrid)**

* **Design:** Create a specific function that evaluates the AI's current state towards a target to determine immediate intent.
    * `function calculate_intent(ai_id, target_id)`: Reads relevant Emotions (Anger, Disgust, Fear towards target), Mental States (Hostility, Sanity, Stress), Personality Traits, Relationship, and situational context.
    * Based on thresholds and combinations, it returns an intent label: `MURDEROUS`, `HOSTILE`, `AVOIDANT`, `NEUTRAL`, `FRIENDLY`, etc.
* **Trigger:** Calculated whenever the AI needs to make a significant decision involving the target.
* **Effect:** The AI's behavior modules directly use this calculated intent label to select actions or dialogue.
* **Pros:** Simpler than a full goal system. Uses existing state information.
* **Cons:** Represents a snapshot evaluation rather than a persistent goal. The intent might flicker if underlying states fluctuate near thresholds. Doesn't explicitly handle planning or long-term striving towards the goal.

**Recommendation:**

For accurately modeling *intent*, **Option 3 (Goal/Drive)** is the strongest approach. It aligns well with modern AI techniques and clearly separates the *motivation* (triggered by emotions/states/events) from the *objective* (the goal) and the *actions* taken.

If a full goal system is too complex for the project scope, **Option 2 (Mental State)**, possibly combined with aspects of **Option 4 (Derived Disposition)**, offers a reasonable approximation by modeling a persistent negative disposition that heavily influences behavior towards a target. Option 1 is generally too simplistic to capture true intent.

**Integration with Architecture (Assuming Goal-Based Approach):**

```mermaid
graph TD
    %% ... (Input, Physiology, Emotion, Mental State Systems as before) ...

    subgraph "State Systems & Blackboard"
        BB[Blackboard <br/>(Stores Emotion, Mental, Physio States)]
        EmotionSystem -- Writes --> BB
        MentalStateSystem -- Writes --> BB
        PhysiologySystem -- Writes --> BB
    end

    subgraph "Goal Management & Behavior"
        GoalInjector[Goal Injector/Trigger Logic]
        GoalStack[AI Goal Stack/List]
        Planner[Planner / Action Selector]
        BehaviorExecutor[Behavior Executor]
        Output(Action / Dialogue / Animation)

        BB -- Reads States --> GoalInjector
        GoalInjector -- Conditions Met --> GoalStack(Push Goal: ELIMINATE Target)
        GoalStack -- Highest Priority Goal --> Planner
        Planner -- Reads World State & BB --> BehaviorExecutor(Select Action: ATTACK Target)
        BehaviorExecutor --> Output
    end

    %% Relationships
    GameEvent --> GoalInjector // Events can trigger goals
```

This shows the state systems feeding into the `Goal Injector`. When conditions are right (based on reading the Blackboard), a high-priority `ELIMINATE` goal is added. The Planner selects this goal and chooses appropriate actions, leading to the "murderous" behavior.