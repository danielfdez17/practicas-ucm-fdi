package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class Sunflower extends Plant {
	
	// CONSTANTS
	public static final int FREQUENCY = 3; 
	public static final int DAMAGE = 0; 
	public static final int COST = 20; 
	public static final int ENDURANCE = 1;
	public static final int SUNCOINS_GENERATED = 10;
	
	// BUILDERS
	public Sunflower() {
		super();
	}
	public Sunflower(GameWorld game, int col, int row) {
		super(game, col, row);
		this.damage = DAMAGE;
		this.cost = COST;
		this.endurance = ENDURANCE;
		this.cycles = -1;
	}
	
	// METHDOS
	// Adds a sun to the game/match every three cycles
	private void addSun() {
		if (this.cycles > 0 && this.cycles % FREQUENCY == 0) {
			this.game.addSun();
		}
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
	@Override
	protected String getSymbol() {
		return Messages.SUNFLOWER_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.SUNFLOWER_NAME_SHORTCUT, COST, DAMAGE, ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.SUNFLOWER_NAME;
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
			this.cycles++;
			this.addSun();	
		}
	}
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
		return this.damage;
	}
	@Override
	public boolean receivePlantAttack(int damage) {
		return false;
	}
	@Override
	public Plant spawn(GameWorld game, int col, int row) {
		return new Sunflower(game, col, row);
	}
}