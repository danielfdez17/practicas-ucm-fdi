package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;

// creo que puede ser la clase padre de todas las plantas
public abstract class Plant extends GameObject {
	
	// ATRIBUTES
	protected int cycles;
	protected int cost;
	
	// BUILDERS
	public Plant() {
		
	}
	public Plant(GameWorld game, int col, int row) {
		super(game, col, row);
	}
	
}