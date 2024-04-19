import java.util.Iterator;

public class BitIterator implements Iterator<Boolean> {

    private int byteLength;
    private byte bitIndex;
    private int byteIndex;
    private static final byte b00000001 = 1;

    private int[] arr;

    public BitIterator(int... bytes) {
        byteLength = bytes.length;
        bitIndex = 0;
        byteIndex = 0;
        arr = new int[byteLength];
        for (int i = 0; i < byteLength; i++) {
            arr[i] = bytes[i];
        }
    }

    @Override
    public boolean hasNext() {
        return (byteIndex<byteLength) && bitIndex<8;
    }

    @Override
    public Boolean next() {
        int value = (arr[byteIndex]>>>(7-bitIndex))&b00000001;
        if(bitIndex==7){
             byteIndex++;
             bitIndex=0;
        }else bitIndex++;
        return value==1;
    }
}
