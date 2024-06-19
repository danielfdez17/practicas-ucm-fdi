package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;

public abstract class Plant extends GameObject {
	
	// ATRIBUTES
	protected int cost;
	
	// BUILDERS
	public Plant() {
		super();
	}
	public Plant(GameWorld game, int col, int row) {
		super(game, col, row);
	}
	
	// METHODS
	// Returns a plant
	public abstract Plant spawn(GameWorld game, int col, int row);
}