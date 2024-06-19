package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class WallNut extends Plant {

	// CONSTANTS
	public static final int ENDURANCE = 10;
	public static final int COST = 50;
	
	// BUILDERS
	public WallNut() {
		super();
	}
	public WallNut(GameWorld game, int col, int row) {
		super(game, col, row);
		this.endurance = ENDURANCE;
		this.cost = COST;
	}

	// METHODS
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
	@Override
	public boolean receivePlantAttack(int damage) {
		return false;
	}
	@Override
	protected String getSymbol() {
		return Messages.WALL_NUT_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.WALL_NUT_NAME_SHORTCUT, COST, 0, ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.WALL_NUT_NAME;
	}
	@Override
	public boolean isAlive() {
		return (this.endurance != 0);
	}
	@Override
	public void onEnter() {}
	@Override
	public void onExit() {}
	@Override
	public void update() {}
	@Override
	public int getEndurance() {
		return this.endurance;
	}
	@Override
	public int getCost() {
		return this.cost;
	}
	@Override
	public int getDamage() {
		return 0;
	}
	@Override
	public Plant spawn(GameWorld game, int col, int row) {
		return new WallNut(game, col, row);
	}
}
