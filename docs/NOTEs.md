# AI emotion system that is data driven.

## Design
- An EmotionComponent with current Valence-Arousal 2D coordinate (VACoordinate) and a radius. An array holding active emotions.
- An Emotion have intensity from 1 to 100, a decay rate, an influence radius and a VACoordinate. Intensity degrade over time with decay rate.
- An external stimulus ( dialogue , event, object ...) can trigger an emotion with intensity and add it to EmotionComponent.
- An active emotion with intensity not zero pull the EmotionComponent's VaCoordinate toward it with pull strength that stronger the further away the target V-A using linear spring model.
- Emotion can link to another emotion with link strength from 1-100, a link strength reaching a threshold range will trigger emotion variant related to source emotion.
- An emotion can combine with another emotion to create a different emotion combine of the 2 emotion ( reference pluchik's wheel of emotion). 

## Components:
EmotionState: Manages the internal state of emotions
EmotionComponent: Handles actor integration and external influences
EmotionSystemLibrary: Provides utility functions for blueprints

## Task:
- Need to rethink how to handle ajacent or link emotion relationship
- Need to rethink how to handle combined emotion relationship
- Need to rethink how to handle opposite emotion relationship

**1. What Game Elements Can Affect AI Emotions?**

Emotions should be influenced by events and states relevant to the AI's goals, relationships, well-being, and perception of the world.

* **Dialogue:**
    * **Content & Tone:** Compliments, insults, threats, questions, reassurances, delivering good/bad news, revealing secrets.
    * **Speaker:** Who is talking? (Friend, enemy, authority figure, stranger). Affects trust, fear, anger responses.
    * **Keywords:** Mentioning the AI's loved ones, fears, goals, past traumas, or faction affiliations.
* **Actions (by Player or other AIs):**
    * **Combat:** Taking damage, dealing damage, witnessing allies/enemies fall, winning/losing fights, being targeted, narrowly escaping.
    * **Social:** Receiving gifts, being helped, being betrayed, being ignored, being followed/led, acts of kindness or cruelty witnessed.
    * **Stealth:** Being detected, successfully sneaking past threats, finding someone hiding.
    * **Exploration:** Discovering valuable resources, entering dangerous/sacred/forbidden locations, encountering specific creatures.
* **Objects & Items:**
    * **Acquisition/Loss:** Gaining or losing important quest items, valuable loot, sentimental objects, necessary tools, or resources (like ammo, food).
    * **Interaction:** Using a specific object (e.g., a trap, a terminal, a comfort item), seeing a significant object (e.g., symbol of their faith, enemy flag).
* **Environment & Game State:**
    * **Location:** Being in a safe zone, enemy territory, dark/scary place, place with positive/negative memories.
    * **World Events:** War declaration, peace treaty, natural disaster, completion of major quests by others.
    * **AI's Status:** Low health/resources, hunger/thirst, status effects (poisoned, blessed), changes in faction reputation.
    * **Time:** Time pressure (e.g., countdown), time of day (if relevant to AI, like fearing darkness).

**2. How These Elements Affect Emotions (Mapping & Translation)**

This is where the "data-driven" aspect meets game logic. The core idea is to translate game events into specific `delta` changes for one or more base emotions.

* **Event-to-Stimulus Mapping:** You need a system (conceptually part of the `InputProcessor` or a dedicated `GameWorldListener`) that takes game event data and outputs calls to the emotion system.
    * *Example 1 (Combat):* `Player deals 30 damage to AI` -> `+15 Fear`, `+20 Anger`, `-10 Joy`.
    * *Example 2 (Dialogue):* `TrustedAlly gives Compliment` -> `+10 Joy`, `+5 Trust`.
    * *Example 3 (Environment):* `AI enters DarkCave area` -> `+10 Fear`, `-5 Trust` (in the surroundings).
    * *Example 4 (Object):* `AI loses QuestItem` -> `+25 Sadness`, `+15 Fear` (of consequences), `-20 Joy`.
* **Context Matters:** The *same* event needs different mappings based on context.
    * `Damage from Enemy` -> High `Anger`, High `Fear`.
    * `Damage from Ally (Betrayal)` -> Very High `Anger`, High `Sadness`, Massive `-Trust`.
    * `Gift from Enemy` -> `+Surprise`, `+Disgust`/`-Trust` (Suspicion).
* **Personality & State Modifiers:** The AI's personality traits (e.g., Brave, Timid, Aggressive, Trusting) and current state (e.g., already angry, low health) should modify the `delta` values.
    * A `Timid` AI might get `+30 Fear` from taking damage, while a `Brave` AI only gets `+5 Fear`.
    * An `Angry` AI might get `+30 Anger` from an insult, while a `Calm` AI only gets `+5 Anger`.
    * An AI already at low health might experience amplified `Fear` responses.
* **Significance:** The magnitude of the `delta` should scale with the event's importance (minor inconvenience vs. major life event).

**3. Interface Design (Conceptual API)**

We need interfaces for the game engine to *inform* the emotion system about events, and for the rest of the AI (decision-making, animation, dialogue selection) to *query* the resulting emotional state.

**A. Input Interfaces (Game Engine -> Emotion System):**

A flexible approach is a generic event handler within the `EmotionStateManager` or a dedicated intermediary.

```python
# Conceptual Python Interface within EmotionStateManager or EventHandler

def process_game_event(ai_id: str, event_type: str, parameters: dict):
    """
    Processes a generic game event and translates it into emotion stimuli.

    Args:
        ai_id: The unique identifier of the AI experiencing the event.
        event_type: A string identifying the type of event (e.g., "COMBAT_DAMAGE_TAKEN", "DIALOGUE_RECEIVED", "ITEM_ACQUIRED").
        parameters: A dictionary containing event-specific details.
            - For "COMBAT_DAMAGE_TAKEN": {"source_id": "player", "amount": 30, "is_critical": False, "weapon_type": "sword"}
            - For "DIALOGUE_RECEIVED": {"speaker_id": "ally_bob", "dialogue_act": "COMPLIMENT", "relationship": "FRIEND", "keywords": ["brave"]}
            - For "ITEM_ACQUIRED": {"item_id": "quest_macguffin", "rarity": "QUEST", "source": "found"}
            - For "AREA_ENTERED": {"area_tag": "DARK_CAVE", "threat_level": "HIGH"}
    """
    # 1. Retrieve AI's personality, current state, relationships (needed for context)
    # personality = get_ai_personality(ai_id)
    # current_emotions = get_current_emotion_state(ai_id)
    # relationship = get_relationship(ai_id, parameters.get("source_id") or parameters.get("speaker_id"))

    # 2. Map event_type and parameters to emotion deltas based on rules, context, personality
    emotion_deltas = map_event_to_stimuli(event_type, parameters, personality, current_emotions, relationship)
    # Example output: emotion_deltas = {"Fear": +15, "Anger": +20, "Joy": -10}

    # 3. Request intensity changes from the core emotion logic
    for emotion_id, delta in emotion_deltas.items():
        # This calls the logic described in the sequence diagram
        request_intensity_change(ai_id, emotion_id, delta)

def request_intensity_change(ai_id: str, emotion_id: str, delta: int):
    """
    Triggers the core emotion update logic (intensity, opposite, links, combinations).
    (This is the function called internally by process_game_event after mapping)
    """
    # ... implementation based on the sequence diagram logic ...
    pass

# --- Helper functions (assumed to exist) ---
# def get_ai_personality(ai_id) -> dict: ...
# def get_current_emotion_state(ai_id) -> dict: ...
# def get_relationship(ai_id_1, ai_id_2) -> str: ... # e.g., "FRIEND", "ENEMY", "NEUTRAL"
# def map_event_to_stimuli(...) -> dict: ... # Contains the complex mapping logic
```

**B. Output Interfaces (Emotion System -> AI Behavior Modules):**

The AI's decision-making, dialogue selection, animation system, etc., need to query the emotional state.

```python
# Conceptual Python Interface within EmotionStateManager or AIBlackboard

def get_current_emotion_state(ai_id: str) -> dict:
    """
    Provides a snapshot of the AI's current emotional state.

    Returns:
        A dictionary, e.g.:
        {
            "dominant_emotion": "Anger",
            "dominant_intensity": 75,
            "dominant_variation": "Rage",
            "all_emotions": {
                "Joy": {"intensity": 5, "variation": "Contentment"},
                "Sadness": {"intensity": 10, "variation": "Melancholy"},
                "Anger": {"intensity": 75, "variation": "Rage"},
                "Fear": {"intensity": 20, "variation": "Fear"},
                # ... etc.
            }
        }
    """
    # ... retrieve and format data from the internal emotion objects ...
    pass

def get_emotion_intensity(ai_id: str, emotion_id: str) -> int:
    """Gets the intensity (0-100) of a specific emotion."""
    # ... retrieve specific value ...
    pass

def get_emotion_variation(ai_id: str, emotion_id: str) -> str:
    """Gets the current variation label of a specific emotion."""
    # ... retrieve specific label ...
    pass

def query_emotional_disposition(ai_id: str, target_id: str = None) -> str:
    """
    Provides a simplified view of the AI's feeling (e.g., for quick dialogue checks).

    Args:
        ai_id: The AI whose emotions are being queried.
        target_id: Optional ID of another character/object the disposition is towards.
                   If provided, considers emotions like Trust/Anger towards that target.

    Returns:
        A simple label like "Positive", "Negative", "Neutral", "Fearful", "Angry", "Mixed".
    """
    # ... logic to combine relevant emotions (e.g., Joy + Trust vs Anger + Fear + Disgust) ...
    pass
```
