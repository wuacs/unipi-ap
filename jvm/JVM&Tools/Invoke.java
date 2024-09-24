class Invoke {

    int i = 5;

    static int add12and13() {
        return 12+13;
    }

    int seti (int k) {
        switch(k) {
            case 100000: return 0;
            case 100001: return 1;
            case 555: return 8;
            case 100005: return 9;
            default: return -1;
        }
    }
    
    public static void main(String[] args) {
    
    }
}