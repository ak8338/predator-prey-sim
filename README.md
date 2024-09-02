# predator-prey-sim
Predator Prey Simulator

The goal of this project is to create a basic two-dimensional simulation that models the interactions between predator and prey. In this simulation, the prey are ants, and the predators are doodlebugs. These creatures live in a 20x20 grid, with each cell able to hold only one critter at a time. The grid is enclosed, so no critter can move outside the boundaries. The simulation progresses in discrete time steps, with each critter performing an action at every step.

Ant Behavior:

	•	Movement: Each time step, an ant tries to move randomly to an adjacent cell (up, down, left, or right). If the chosen cell is occupied or would take the ant out of bounds, the ant stays in its current position.
	•	Breeding: After surviving three time steps, an ant can breed at the end of the time step. It will produce offspring in an adjacent empty cell. If no adjacent cells are empty, breeding does not occur. Once an ant breeds, it must wait three more time steps before it can breed again.

Doodlebug Behavior:

	•	Movement: Each time step, a doodlebug looks for an adjacent ant (up, down, left, or right) and moves to that cell to eat the ant. If no adjacent ant is found, the doodlebug moves in the same way as the ants. A doodlebug cannot eat other doodlebugs.
	•	Breeding: After surviving eight time steps, a doodlebug can spawn a new doodlebug in the same way ants breed.
	•	Starvation: If a doodlebug fails to eat an ant for three consecutive time steps, it will starve and be removed from the grid.

The simulation continues until all doodlebugs move before the ants do. The world is displayed using ASCII characters, with “o” representing ants, “X” representing doodlebugs, and “-” representing empty spaces. You will create a base class, Organism, encapsulating shared data and behavior for both ants and doodlebugs. The Organism class will include a virtual function for movement, which the derived classes for ants and doodlebugs will implement. Additionally, you may need to use auxiliary data structures to keep track of which critters have moved during each time step.
