    private static void compressAndWrite(int[][] arr, long bitRowWidth, long height){
        ArrayList<Long> unsizedSeriasLengths = new ArrayList<>(); 
        boolean currentSymbol = true;
        long currentSeriaLength = 0;
        boolean isFirstWhite = ((arr[0][0] >>> 7) & 1) == 1;

        for (int i = 0; i < arr.length; i++) {
            int j = 0;
            var iterator = new BitIterator(arr[i]);
            while (iterator.hasNext() && (bitRowWidth > j++)) {
                boolean bit = iterator.next();
                if (bit == currentSymbol) {
                    currentSeriaLength++;
                } else {
                    unsizedSeriasLengths.add(currentSeriaLength);
                    currentSeriaLength = 1;
                    currentSymbol = currentSymbol ? false : true;
                }
            }
        }
        unsizedSeriasLengths.add(currentSeriaLength);

        System.out.println("Длины серий:");
        System.out.println(unsizedSeriasLengths);
        int[] possibleCodeSizes = new int[25];
        for (int i = 3; i <= 24; i++) {
            possibleCodeSizes[i] = getEncodingBitLengthBy(i, unsizedSeriasLengths, isFirstWhite);
        }
        int minIndex = 3;
        int min = possibleCodeSizes[3];
        for (int i = 4; i <= 24; i++) {
            if (possibleCodeSizes[i] < min) {
                minIndex = i;
                min = possibleCodeSizes[i];
            }
        }
        int codeLength = minIndex;
        System.out.println("Первый пиксель " + (isFirstWhite ? "" : "не ") + "белый");
        System.out.println("Минимальный размер кода " + min + "bit при длине кода " + codeLength + "bit");
        long maxValue =
                getMaxValueForCodeLength(codeLength); 
        var brc = new BitRowConstructor(min, codeLength);
        for (int i = 0; i < unsizedSeriasLengths.size(); i++) {
            int seriaSize = unsizedSeriasLengths.get(i).intValue();
            if (seriaSize > 0) {
                seriaSize -= maxValue;
                while (seriaSize > 0) {      //пока серия не доразбита пишем две серии (maxValue и 0)
                    brc.write((int) maxValue); //
                    brc.write(0);
                    seriaSize -= maxValue;
                }
                if (seriaSize != 0) { 
                    brc.write((int) (seriaSize + maxValue));
                }
            } else {
                brc.write(0);
            }
        }
        writeCompressed(codeLength, bitRowWidth, height, brc.getBytesAndFinish());
    }
    private static void decompressAndWrite(int[] compressedSerias, int codeLength, long width, long height) {
        BitIterator bi = new BitIterator(compressedSerias);
        SeriaIterator si = new SeriaIterator(bi, codeLength);
        ArrayList<Integer> decompressedSerias = new ArrayList<>();
        while (si.hasNext()) {
            decompressedSerias.add(si.next());
        }
        System.out.println("Восстановленные длины серий (чередование белый-черный-белый...):");
        System.out.println(decompressedSerias);

        BitRowConstructor brc1 = new BitRowConstructor((int) (width * height), 1);
        int color = 1;
        for (Integer ser : decompressedSerias) { //пишем цвет в строку нужное кол-во раз
            for (int i = 0; i < ser.intValue(); i++) {
                brc1.write(color);
            }
            color = color == 1 ? 0 : 1; //переключаем цвет
        }
        var decompressedMatrix = brc1.getBytesAndFinish();

        System.out.println("Восстановленные данные:");
        BitIterator bi1 = new BitIterator(decompressedMatrix);
        int fWidth = formatedLengthOf((int) width); 
        int[][] splitedMatrix = new int[(int) height][fWidth];
        for (int i = 0; i < height; i++) { 
            BitRowConstructor rc = new BitRowConstructor(splitedMatrix[i], 1);
            for (int j = 0; j < width; j++) {
                rc.write(bi1.next());
            }
            var row = rc.getBytesAndFinish();
        }
        long rastrsize = height * fWidth;
        int[] rastrsizeArr = longToByteArrayLittleEndian(rastrsize);
        int[] wArr = longToByteArrayLittleEndian(width);
        int[] hArr = longToByteArrayLittleEndian(height);
        int[] filesizeArr = longToByteArrayLittleEndian(rastrsize + 62);
        writeDecompressed(filesizeArr, wArr, hArr, rastrsizeArr, splitedMatrix);
    }
