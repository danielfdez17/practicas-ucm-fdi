package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class Sporty extends Zombie {

	// CONSTANTS
	public static final int ENDURANCE = 2;
	public static final int DAMAGE = 1;
	public static final int SPEED = 1;
	public static final int INDEX = 2;
	
	// BUILDERS
	public Sporty() {
		super();
	}
	public Sporty(GameWorld game, int col, int row) {
		super(game, col, row);
		this.endurance = ENDURANCE;
		this.damage = DAMAGE;
		this.cycles = 0;
	}
	
	// METHODS
	@Override
	public int getIndex() {
		return INDEX;
	}
//	@Override
//	public boolean receivePlantAttack(int damage) {
//		boolean recieve = false;
//		if (this.endurance > 0) {
//			recieve = true;
//			this.endurance -= damage;
//			if (this.endurance < 0) {
//				this.endurance = 0;
//			}
//		}
//		return recieve;
//	}
	@Override
	protected String getSymbol() {
		return Messages.SPORTY_ZOMBIE_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.zombieDescription(this.getSymbol(), SPEED, DAMAGE, ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.SPORTY_ZOMBIE_NAME;
	}
	@Override
	public boolean isAlive() {
		return (this.endurance != 0);
	}
	@Override
	public void update() {
		if (this.isAlive()) {
			GameItem item = game.getGameItemInPosition(this.col - 1, this.row);
			if (item != null) {
				if (!item.receiveZombieAttack(this.damage) && (this.cycles > 0 && this.cycles % SPEED == 0)) {
					if (!item.fillPosition()) {
						this.col--;
					}
				}
			}
			else {
				if (this.cycles > 0 && this.cycles % SPEED == 0) {
					this.col--;	    		
				}
			}
			this.cycles++;
		}
		else {
			this.game.setZombiesAlived();
		}
	}
	@Override
	public int getEndurance() {
		return this.endurance;
	}
	@Override
	public Zombie spawn(GameWorld game, int col, int row) {
		return new Sporty(game, col, row);
	}
}