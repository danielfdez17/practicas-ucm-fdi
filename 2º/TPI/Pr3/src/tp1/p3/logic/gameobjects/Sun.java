package tp1.p3.logic.gameobjects;

import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class Sun extends GameObject {
	
	// CONSTANTS
	public static final int ENDURANCE = 11;
	public static final int SUNCOINS = 10;
	
	// BUILDERS
	public Sun(GameWorld game, int col, int row){
		this.game = game;
		this.col = col;
		this.row = row;
		this.endurance = ENDURANCE;
	}

	// METHODS
	@Override
	public boolean receiveZombieAttack(int damage) {
		return false;
	}
	@Override
	public boolean receivePlantAttack(int damage) {
		return false;
	}
	@Override
	public boolean catchObject() {
		this.endurance = 0;
		this.game.addCatchedSuns();
		return true;
	}
	@Override
	public boolean fillPosition() {
		return false;
	}
	@Override
	protected String getSymbol() {
		return Messages.SUN_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.SUN_DESCRIPTION;
	}
	@Override
	public String getName() {
		return "";
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
	public void update() {
		if (this.isAlive()) {
			this.endurance--;	
		}
	}
	@Override
	public int getEndurance() {
		return this.endurance;
	}
	@Override
	public int getCost() {
		return 0;
	}
	@Override
	public int getDamage() {
		return 0;
	}
}