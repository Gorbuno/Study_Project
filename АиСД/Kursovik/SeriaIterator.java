public class SeriaIterator {
    BitIterator bi;
    int cl;
    private boolean hasNext = true;
    public SeriaIterator(final BitIterator bi, int codeLength) {
        this.bi = bi;
        this.cl = codeLength;
    }
    public boolean hasNext() {
        return hasNext;
    }

    public int next() { //getSeriaLength
        int val = 0;
        for (int i = 0; i < cl; i++) {
            val = val << 1;
            if (!bi.hasNext()) {
                hasNext = false;
                return 0;
            }
            int bit = bi.next() ? 1 : 0;
            val = val | bit;
        }
        return val;
    }
}
