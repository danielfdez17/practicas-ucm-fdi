package tp1.p3.logic.gameobjects;

import tp1.p3.logic.GameWorld;

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
	@Override
	public boolean receivePlantAttack(int damage) {
		return false;
	}
	@Override
	public boolean receiveZombieAttack(int damage) {
		boolean recieve = false;
		if (this.endurance > 0) {
			recieve = true;
			this.endurance -= damage;
			if (this.endurance < 0) {
				this.endurance = 0;
			}
		}
		return recieve;
	}
	// Returns a plant
	public abstract Plant spawn(GameWorld game, int col, int row);
}