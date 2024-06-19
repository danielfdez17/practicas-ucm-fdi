package tp1.p3.control.exceptions;

public class NotCatchablePositionException extends InvalidPositionException {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5121708617275326740L;
	
	public NotCatchablePositionException(String message) {
		super(message);
	}
	
	public NotCatchablePositionException(Throwable cause) {
		super(cause);
	}

	public NotCatchablePositionException(String message, Throwable cause) {
		super(message, cause);
	}

}
