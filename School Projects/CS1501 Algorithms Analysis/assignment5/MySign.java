import java.io.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.lang.instrument.*;
import java.util.*;
/**
 *
 * @author Chris
 */
public class MySign {

    //Checks to make sure the arguments are correctly entered for MySign to run
    public static void main(String[] args) {
       if(args.length == 2){
           if(args[0].equals("s") || args[0].equals("v")){
               if(args[0].equals("s")){
                   signing(args[1]);
               }
               else{
                   verifying(args[1]);
               }
           }else{
               System.out.println("Enter the correct arguement for signing or verifying");
           }
       }
       else{
           System.out.println("Please enter the correct arguments from the command line");
           System.exit(0);
       }
    }
    //Creating the hash from the file and then decrypting it using private keys
    public static void signing(String fileName){
        try {
			File privKey = new File("privkey.rsa");
                        //Reads in the correct keys into BigIntegers to be used
                        if(privKey.exists() && !privKey.isDirectory() ){
                            ObjectInputStream inputPriv = new ObjectInputStream(new FileInputStream("privkey.rsa"));
                            BigInteger d = (BigInteger) inputPriv.readObject();
                            BigInteger n = (BigInteger) inputPriv.readObject();
                            

                            Path path = Paths.get(fileName);
                            byte[] data = Files.readAllBytes(path);
                            
                            
			// create class instance to create SHA-256 hash
			MessageDigest md = MessageDigest.getInstance("SHA-256");

			// process the file
			md.update(data);
			// generate a has of the file
			byte[] digest = md.digest();

			// convert the bite string to a printable hex representation
			// note that conversion to biginteger will remove any leading 0s in the bytes of the array!
			String result = new BigInteger(1, digest).toString(16);
                        
                        BigInteger myHash = new BigInteger(1,digest);
			// print the hex representation
					
                        BigInteger decryptHash = myHash.modPow(d, n);
						//Decrypts the hash by setting it to the Dth mod n
                        
                        
                        //Crates new file with .signed extension that has Hash and original contents
                        String signedFileName = fileName + ".signed";
                        
						
						//Writes BigInteger as well as original contents to new file
                        FileOutputStream output = new FileOutputStream(signedFileName);
                        ObjectOutputStream out = new ObjectOutputStream(output);
                        
                        out.writeObject(decryptHash);
                        out.writeObject(data);
                        out.close();

                        }
                        else{
                            System.out.println("Private Key RSA does not exist");
                            System.exit(1);
                        }
		}
		catch(IOException | ClassNotFoundException | NoSuchAlgorithmException e) {
			System.out.println(e.toString());
		}
    }
   
   //Method that reads in file, encrypts the hash and then compares it to check validity
    public static void verifying(String fileName){
        try {
			File privKey = new File("pubkey.rsa");
                        
                        if(privKey.exists() && !privKey.isDirectory() ){
                            ObjectInputStream inputPriv = new ObjectInputStream(new FileInputStream("pubkey.rsa"));
                            BigInteger e = (BigInteger) inputPriv.readObject();
                            BigInteger n = (BigInteger) inputPriv.readObject();

                           File checkFile = new File(fileName);
                           byte[] test = new byte[(int) checkFile.length()];
                            
                            FileInputStream in = new FileInputStream(fileName);
                            ObjectInputStream input = new ObjectInputStream(in);
                            
                            
                            BigInteger decryptedHash = (BigInteger) input.readObject();
                            
                            byte[] readFile = (byte []) input.readObject();

                            input.close();
       
			// create class instwance to create SHA-256 hash
			MessageDigest md = MessageDigest.getInstance("SHA-256");
                        
			// process the file
			md.update(readFile);
			// generate a has of the file
			byte[] digest = md.digest();

			// convert the bite string to a printable hex representation
			// note that conversion to biginteger will remove any leading 0s in the bytes of the array!
			
                        
                        BigInteger myHash = new BigInteger(1,digest);
			// print the hex representation
                        BigInteger decryptHash = decryptedHash.modPow(e, n);
                        
                       
                        //Checks the signature to see if the created Hash is the same as the one that has been calculated
                        if(myHash.compareTo(decryptHash) == 0){
                            System.out.println("The signature is valid");
                        }
						else{
							System.out.println("The signature is not valid");
						}
                    }
                        
                    else{
                            System.out.println("Public Key RSA does not exist");
                            System.exit(1);
                    }
		}
		catch(IOException | ClassNotFoundException | NoSuchAlgorithmException e) {
			System.out.println("There was an error with the file" + e.toString());
		}
    }
}
