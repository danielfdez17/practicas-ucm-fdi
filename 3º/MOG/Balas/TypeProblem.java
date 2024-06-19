public enum TypeProblem {
    MAXIMIZAR, MINIMIZAR;
   
    public static synchronized TypeProblem getType(String t) {
        return MAXIMIZAR.name().toLowerCase().contains(t) ? MAXIMIZAR : MINIMIZAR;
    }
}
