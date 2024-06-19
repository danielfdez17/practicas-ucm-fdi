package tp.pr0;

public class FuncsMatematicas {
	public static int factorial (int n) {
		int fact = 1;
		if (n < 0) {
			fact = 0;
		}
		else if (n == 0) {
			fact = 1;
		}
		else {
			while (n != 0) {
				fact *= n;
				n--;
			}
		}
		return fact;
	}
	public static int combinatorio (int n, int k) {
		int combi = 0;
		if ((n >= k) && (k >= 0)) {
			if (k > n) {
				combi = 0;
			}
			else {
				int n_fact = factorial(n);
				int k_fact = factorial(k);
				int dif_fact = factorial(n-k);
				combi = n_fact / (k_fact * dif_fact);
			}
		}
		else if ((n < 0) || (k < 0)) {
			combi = -1;
		}
		return combi;
	}
	public static void main(String[] args) {
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j <= i; ++j) {
				System.out.print(FuncsMatematicas.combinatorio(i, j) + " ");
			}
			System.out.println();
		}
	}
}
