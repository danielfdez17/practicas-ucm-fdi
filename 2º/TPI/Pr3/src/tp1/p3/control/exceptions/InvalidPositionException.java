package tp1.p3.control.exceptions;

public class InvalidPositionException extends GameException {

	/**
	 * 
	 */
	private static final long serialVersionUID = -8050390178436586907L;
	
	public InvalidPositionException(String message) {
		super(message);
	}
	
	public InvalidPositionException(Throwable cause) {
		super(cause);
	}

	public InvalidPositionException(String message, Throwable cause) {
		super(message, cause);
	}

}
