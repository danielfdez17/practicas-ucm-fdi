package tp1.p3.logic.gameobjects;

import tp1.p3.logic.GameItem;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class Peashooter extends Plant {
	
	// CONSTANTS
	public static final int DAMAGE = 1; 
	public static final int COST = 50; 
	public static final int ENDURANCE = 3; 

	// BUILDERS
	public Peashooter() {
		super();
	}
	public Peashooter(GameWorld game, int col, int row) {
		super(game, col, row);
		this.damage = DAMAGE;
		this.cost = COST;
		this.endurance = ENDURANCE;
	}

	// METHODS
	// Shoots a zombie in front of the peashooter if it is found
	private void shoot() {
		int i = this.col + 1;
		boolean found = false;
		GameItem item;
		while ((i < GameWorld.NUM_COLS) && !found) {
			item = game.getGameItemInPosition(i, this.row);
			if (item != null) {
				found = item.receivePlantAttack(this.damage);
			}
			i++;
		}
	}
	@Override
	protected String getSymbol() {
		return Messages.PEASHOOTER_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.PEASHOOTER_NAME_SHORTCUT, COST, DAMAGE, ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.PEASHOOTER_NAME;
	}
	@Override
	public void update() {
		if (this.isAlive()) {
			this.shoot();
		}
	}
	@Override
	public int getCost() {
		return this.cost;
	}
	@Override
	public Plant spawn(GameWorld game, int col, int row) {
		return new Peashooter(game, col, row);
	}
}