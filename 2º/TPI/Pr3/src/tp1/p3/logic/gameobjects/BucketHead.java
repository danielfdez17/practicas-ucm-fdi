package tp1.p3.logic.gameobjects;

import tp1.p3.logic.GameItem;
import tp1.p3.logic.GameWorld;
import tp1.p3.view.Messages;

public class BucketHead extends Zombie {

	// CONSTANTS
	public static final int ENDURANCE = 8;
	public static final int DAMAGE = 1;
	public static final int SPEED = 4;
	public static final int INDEX = 1;
		
	// BUILDERS
	public BucketHead() {
		super();
	}
	public BucketHead(GameWorld game, int col, int row) {
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
	@Override
	protected String getSymbol() {
		return Messages.BUCKET_HEAD_ZOMBIE_SYMBOL;
	}
	@Override
	public String getDescription() {
		return Messages.zombieDescription(this.getSymbol(), SPEED, DAMAGE, ENDURANCE);
	}
	@Override
	public String getName() {
		return Messages.BUCKET_HEAD_ZOMBIE_NAME;
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
			this.onExit();
			this.game.setZombiesAlived();
		}
	}
	@Override
	public Zombie spawn(GameWorld game, int col, int row) {
		return new BucketHead(game, col, row);
	}
}