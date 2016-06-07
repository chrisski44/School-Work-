import java.math.BigInteger;
import java.util.*;
import java.io.*;

/**
 *
 * @author Chris
 */
public class MyKeyGen {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        BigInteger p = new BigInteger(512, 100, new Random()); //Generate two 512 Big Integers to get a key of 1024
        BigInteger q = new BigInteger(512, 100, new Random());
        
        BigInteger n = p.multiply(q); //Multiply my random numbers
        
		
		//Calculate phi of n by doing (p-1)*(q-1)
        BigInteger phiOfN = (p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE)));
        
        
        
        
        BigInteger e = new BigInteger("65537"); //Suggested e value from the book code
        
        BigInteger d = e.modInverse(phiOfN); // Do the modular inverse of phiOfN for e
        
        /*
		Using object output stream to create new files that contain the public and private
		keys that are to be used in MySign.java. The BigInteger objects are serialized into the 
		correct files
		*/
        try{
            File priv = new File("privkey.rsa");
            File pub = new File("pubkey.rsa");
            
            
           OutputStream privKey = new FileOutputStream("privkey.rsa");
           OutputStream pubKey = new FileOutputStream("pubkey.rsa");
           ObjectOutputStream privOutput = new ObjectOutputStream(privKey);
           ObjectOutputStream pubOutput = new ObjectOutputStream(pubKey);
           
           privOutput.writeObject(d);
           
           privOutput.writeObject(n);
           
           pubOutput.writeObject(e);
           pubOutput.writeObject(n);
           
           pubKey.close();
           privKey.close();
        }catch(IOException exception){
            System.out.println(exception.getMessage());
        }
    }
    
    
   
}



