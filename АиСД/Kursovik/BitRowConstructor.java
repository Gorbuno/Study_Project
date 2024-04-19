public class BitRowConstructor {
    private int[] bytes;
    private int byteIndex = 0;
    private int bitIndexToRecord = 0;

    boolean workIsDone = false;

    private int codeLength;
    public BitRowConstructor(int sizeBits, int codeLength) {
        bytes = new int[sizeBits/8 + ((sizeBits%8)>0?1:0)];
        this.codeLength = codeLength;
    }

    public BitRowConstructor(int[] arr, int codeLength) {
        bytes = arr;
        this.codeLength = codeLength;
    }
    public void write(int value){
        for (int i = 1; i <= codeLength; i++) {
            int bit = (value>>(codeLength-i))&1;
            bytes[byteIndex] = bytes[byteIndex]|bit;
            bitIndexToRecord++;
            if(bitIndexToRecord > 7){
                byteIndex++;
                bitIndexToRecord =0;
            }else{
                bytes[byteIndex] = bytes[byteIndex]<<1;
            }
        }
    }
    public void write(boolean value){
        for (int i = 1; i <= codeLength; i++) {
            int bit = value?1:0;
            bytes[byteIndex] = bytes[byteIndex]|bit;
            bitIndexToRecord++;
            if(bitIndexToRecord > 7){
                byteIndex++;
                bitIndexToRecord =0;
            }else{
                bytes[byteIndex] = bytes[byteIndex]<<1;
            }
        }
    }
    public int[] getBytesAndFinish(){
        if(!workIsDone){
            if (byteIndex<bytes.length){
                bytes[byteIndex]=bytes[byteIndex]<<(7 - bitIndexToRecord); //заполняет пустые биты
            }
            workIsDone=true;
            return bytes;
        }else return null;
    }
