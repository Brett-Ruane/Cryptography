import java.lang.Math;
import java.util.Random;
import java.util.ArrayList;

public class MathRandomAttack 
{

	
	static final double q  = Math.pow(2, 48);
	static final double w  = Math.pow(2, 22);
	static final long a    = 0x5DEECE66DL;
	static final long b    = 0x0BL;   

	public static void main(String args[])
	{
		System.out.println("q = " + q);		
		System.out.println("w = " + w);		
		System.out.println("a = " + a);		
		System.out.println("b = " + b);		

		//double r = Math.random();
		long sd = 277099744860301L;
		Random rand = new Random(sd);
		double r = rand.nextDouble();
		printBitInfo(r, "r");
		double r2 = rand.nextDouble();
		printBitInfo(r2, "r2");


		double seedGuess = seedFromMathDotRandomOutput(r);
		//printBitInfo(seedGuess, "seedGuess");

		double seedGuess2 = seedFromMathDotRandomOutput(r2);
		//printBitInfo(seedGuess2, "seedGuess2");

		blumMicaliConstructionVariant(r, 2);
		
		//System.out.println("\nr mantissa         = " + getMantissa(r) + "\nseedGuess mantissa = " + getMantissa(seedGuess));
	}

	public static double seedFromMathDotRandomOutput(double r)
	{
		return (r * w);
	}

	public static void blumMicaliConstructionVariant(double seed, int n) // n == # of r_i's
	{
		long numerator = (long)(seed * (1L << 53));
		int first26 = (int)(numerator >>> 27);
        	int last27 = (int)(numerator & ((1L << 27) - 1));
		final long mask = (1L << 48) - 1;
		System.out.println("numerator = " + numerator + "\nfirst26 = " + first26 + "\nlast27 = " + last27);
		long upperMOf48Mask = ((1L << 27) - 1) << (48 - 27);
		long oldSeedUpperN = ((long)first26 << (48 - 26)) & mask;
        	long newSeedUpperM = ((long)last27 << (48 - 27)) & mask;
		ArrayList<Long> possibleSeeds = new ArrayList<Long>();
		for (long oldSeed = oldSeedUpperN; oldSeed <= (oldSeedUpperN | ((1L << (48 - 26)) - 1)); oldSeed++) 
		{
            		long newSeed = (oldSeed * a + b) & mask;
            		if ((newSeed & upperMOf48Mask) == newSeedUpperM) 
			{
                		possibleSeeds.add(newSeed);
           		}
        	}

        	if (possibleSeeds.size() == 1) {
            		System.out.println("FOUDN SEED = " + (possibleSeeds.get(0) ^ a)); // setSeed(x) sets seed to `(x ^ multiplier) & mask`, so we need another `^ multiplier` to cancel it out
        	}	
	
		/*
		int i = 1;
		double s_i = seed;
		while (i <= n) 
		{	
			double r_i = s_i / w; // took floor out here 	
			s_i = ((a * s_i) + b) % q;
			printBitInfo(s_i, "s_" + i);
			printBitInfo(r_i, "r_" + i);
			i++;
		}
		//return r_i;
		*/
	}
	
	public static String getMantissa(double r)
	{
		long bits = Double.doubleToRawLongBits(r);
             	String binaryRepresentation = String.format("%64s", Long.toBinaryString(bits)).replace(' ', '0');
		return binaryRepresentation.substring(12);
	}

	public static void printBitInfo(double r, String name)
	{
		long bits = Double.doubleToRawLongBits(r);
		String binaryRepresentation = String.format("%64s", Long.toBinaryString(bits)).replace(' ', '0');
		String sign = binaryRepresentation.substring(0, 1);
        	String exponent = binaryRepresentation.substring(1, 12);
        	String mantissa = binaryRepresentation.substring(12);
		System.out.println("\nName:        " + name);
		System.out.println("Double Val:  " + r);
        	System.out.println("Sign:        " + sign);
        	System.out.println("Exponent:    " + exponent);
        	System.out.println("Mantissa:    " + mantissa);
        	System.out.println("Binary:      " + binaryRepresentation);
	}
	
}
