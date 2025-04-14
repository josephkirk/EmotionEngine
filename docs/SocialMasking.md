
# Social Masking

## Statements
Modeling fake or "projected" emotions where the AI's external expression contradicts its internal state (like a happy tone but sad facial expression) is a fascinating challenge! This requires explicitly separating the AI's internal feelings from its external performance.

Here’s a design approach:

**1. Core Concept: Separation of Internal State & External Expression**

* **Internal State:** This is what the AI *actually* feels, managed by the Emotion, Mental State, and Physiology systems we've discussed. (e.g., Internally: High `Sadness`, Low `Joy`, High `Stress`).
* **External Expression:** This is what the AI *chooses* to display through various channels. It might match the internal state or be deliberately different (a "mask").
* **Decision Layer ("Social Filter / Masking Logic"):** A crucial component that decides *whether* to fake emotions and *what* expression to project onto which channel.

**2. Why Fake Emotions? (Triggers for the Decision Layer)**

The decision to project a fake emotion depends on context:

* **Social Norms:** Hiding grief at a formal event.
* **Deception:** Appearing friendly to lure a target, faking confidence when scared.
* **Manipulation:** Feigning sadness for sympathy, faking enthusiasm to persuade.
* **Self-Preservation:** Hiding fear from an aggressor.
* **Maintaining Composure:** Suppressing anger or fear under pressure or orders (e.g., a stoic guard).
* **Internal Goals:** Trying to achieve an objective that requires a specific emotional presentation.

**3. Modeling External Expression Channels**

The AI expresses itself through multiple channels, and control over these might vary:

* **Dialogue Content:** Choice of words (often highly controllable).
* **Vocal Tone:** Pitch, cadence, volume (consciously controllable to a degree, but can leak stress).
* **Facial Expression:** Main expressions (consciously controllable), but micro-expressions can leak true feelings.
* **Body Language:** Posture, gestures (partly controllable, but often leaks underlying states like tension, sadness, fear).

**4. The "Leakage" Problem (Conflicting Signals)**

This is key to your example (happy tone, sad face). Leakage occurs when the AI tries to project one emotion, but the true internal state subtly (or obviously) influences one or more expression channels.

* **Causes of Leakage:**
    * **High Internal Intensity:** Very strong true emotions are harder to mask completely.
    * **High Stress / Low Focus / Low Sanity:** Compromised mental state makes it harder to maintain the facade.
    * **Lack of Skill/Practice:** An AI not skilled in deception (personality trait) might leak more.
    * **Channel Difficulty:** Body language or micro-expressions are harder to consciously control than word choice.
    * **Sudden Events:** Being surprised or put under sudden pressure can break composure.

**5. Architecture & Integration**

We need a place for the "Decision Layer" and a way to manage the separate internal vs. external states.

**Recommended Approach: Explicit Expression Controller / Filter Layer**

This provides the cleanest separation.

```mermaid
graph TD
    subgraph "Internal State Systems"
        direction LR
        P[Physiology State]
        E[Emotion State]
        M[Mental State]
        G[Active Goals / Intent]
    end

    subgraph "Context & Personality"
        CTX[Social Context / World State]
        PERS[AI Personality / Traits]
    end

    subgraph "Decision & Expression"
        DecisionLayer{Expression Decision Logic <br/> (Social Filter / Masking)}
        InternalStateSummary([Internal State Summary]) --> DecisionLayer
        CTX --> DecisionLayer
        PERS --> DecisionLayer
        G --> DecisionLayer

        DecisionLayer --> ProjectedState{Projected Expression State <br/> (May vary per channel)}
    end

    subgraph "Output Channels / Behavior Modules"
        direction LR
        Dialogue[Dialogue System]
        Animation[Animation System <br/> (Face, Body)]
        Audio[Audio System <br/> (Vocal Tone)]

        ProjectedState --> Dialogue(Select Content/Tone)
        ProjectedState --> Animation(Select Face/Body Animation)
        ProjectedState --> Audio(Select Vocal Modulation)
    end

    %% Data Flow Summary
    InternalStateSummary <== P & E & M
```

**How it Works:**

1.  **Internal State:** Physiology, Emotion, Mental State systems determine the AI's true internal state. Active Goals and Personality also play a role.
2.  **Decision Layer (`Expression Decision Logic`):**
    * Reads the true Internal State summary.
    * Reads Social Context (who is present, situation).
    * Reads AI's Goals (what is it trying to achieve?).
    * Reads AI's Personality (is it deceptive, stoic?).
    * **Decides:** Based on rules/logic: Should I project my true state or a fake one?
    * **Determines Projection:** If faking, *what* emotion should be projected? (e.g., project "Happy" even though internal state is "Sad").
    * **Applies Leakage:** Based on internal intensity, stress, skill etc., it determines the final output for *each channel*. This is where conflicts arise.
        * *Example Rule:* `If InternalSadness > 70 AND Goal = 'AppearHappy' AND Stress > 50 THEN ProjectedState = {Vocal: Happy, Dialogue: Happy, Facial: Happy(Leak_MicroSadness), Body: Sad_Subtle}`
3.  **Projected State:** This structure holds the target expression for each output channel. It might be consistent ("Happy" across all) or conflicting ("Happy" vocal, "Sad" body).
4.  **Output Modules:** The Dialogue, Animation, and Audio systems read this `ProjectedExpressionState` and execute the corresponding outputs. The Animation system might need specific animations for subtle sadness posture or micro-expressions.

**Implementing Leakage:**

* **Conditional Override:** If leakage conditions are met, set one channel (e.g., Body Language) to represent the true emotion while others show the fake one.
* **Blending:** Use animation layers or blend shapes to mix expressions (e.g., 80% projected smile, 20% underlying frown).
* **Micro-expressions:** Trigger brief (few frames) animations of the true emotion overlayed on the projected one.
* **Parameter Modulation:** Slightly alter parameters of the projected expression (e.g., a "Happy" vocal tone might have a subtle tremor if internal Fear is high).

**Conclusion:**

Modeling fake emotions requires separating the AI's internal state from its external expression. An "Expression Decision Layer" (or Social Filter) determines the projected emotion based on internal state, goals, personality, and context. Crucially, this layer must also model potential "leakage," allowing true emotions to subtly influence certain expression channels (like body language or micro-expressions) even when the AI is trying to project something else, leading to believable conflicting signals.