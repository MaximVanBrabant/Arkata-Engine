Design Patterns:
	- basic Update method
	- Component system - > adding components to a gameObject 
		different kinds of components:
						transform, collider, keyboardInput, sprite, 
						every component inherits from the base component that 
						has a Update / Render / Initialize function
						
	- Collision system -> collisionManager = handles all of the collision between all the objects with colliders + the enemyAI colliders
	I use tags for the colliders so then I know which kind of types of gameobject have collided with eachother and then through an enum i give that a specific kind of 
	collisionType depending on the tags
	then depending on the collisionType, specific code will be executed.

	- AI system -> every enemy has collisionboxes that define the environment they can see. using this i can manipulate their behavior dependant on what they can see in the collision boxes
	- State machine system -> player + AI uses a state machine to define the different kind of behaviors they can do
	- Observer pattern: observer pattern is used for the game context so the game knows when to swap to a different level -> when all enemies died
	it's also used for the UI -> to know if a player got hit + if he picked up a item


link to github repo:
https://github.com/MaximVanBrabant/BubbleBobble
