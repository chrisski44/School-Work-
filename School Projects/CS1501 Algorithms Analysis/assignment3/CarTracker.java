import java.util.Scanner;

/**
 *
 * @author Chris
 */
public class CarTracker {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        MilePriority mileCompare = new MilePriority();
        PricePriority priceCompare = new PricePriority();
        MinPQ pqMile = new MinPQ(100, mileCompare);
        MinPQ pqPrice = new MinPQ(100, priceCompare);

        int menuChoice = 0;

        Scanner scan = new Scanner(System.in);
        do {

            System.out.println("Welcome to Car Tracker");
            System.out.println("Please select one of the following menu options below"
                    + "by entering the designated number");
            System.out.println("1.) Add a car");
            System.out.println("2.) Update a car");
            System.out.println("3.) Remove a specific car from consideration");
            System.out.println("4.) Retrieve the lowest price car");
            System.out.println("5.) Retrieve the lowest mileage car");
            System.out.println("6.) Retrieve lowest price car by make and model");
            System.out.println("7.) Retrieve the lowest mileage car by make and model");
            System.out.println("8.) Exit the program");
            menuChoice = scan.nextInt();

            switch (menuChoice) {
                case 1:
                    Scanner input = new Scanner(System.in);
                    String VIN;
                    String model;
                    String make;
                    int price;
                    int mileage;
                    String color;
                    boolean valid = false;

                    System.out.println("Please enter a unique VIN number for car (Must be 17 characters with no I(i), O(o)"
                            + "or Q(q)");

                    VIN = input.nextLine();
                    System.out.println("Please enter a make");
                    make = input.nextLine();
                    
                    System.out.println("Please enter a model");
                    model = input.nextLine();
                    
                    System.out.println("Please enter a price");
                    price = input.nextInt();
                    System.out.println("Please enter mileage");
                    mileage = input.nextInt();
                    System.out.println("Enter a color");
                    color = input.next();

                    Car car = new Car(VIN, make, model, price, mileage, color);
                    pqMile.insert(car);
                    pqPrice.insert(car);
                    break;
                case 2:
                     System.out.println("Type the VIN of the car you want to update");
                     input = new Scanner(System.in);
                     String findVIN = input.next();
                     Car newCar = pqPrice.findEntry(findVIN);
                     if(newCar == null){
                         System.out.println("This VIN was not found");
                     }
                     else{
                         System.out.println(newCar);
                         System.out.println("Which would entry would you like to update? \n");
                         System.out.println("1.) VIN Number");
                         System.out.println("2.) Make");
                         System.out.println("3.) Model");
                         System.out.println("4.) Price");
                         System.out.println("5.) Mileage");
                         System.out.println("6.) Color");
                         int entry = input.nextInt();
                         if(entry < 7 && entry > 0){
                             
                                 System.out.println("What would you like to change the value to");
                                 String change = input.next();
                                 boolean success = pqPrice.updateEntry(findVIN, change, entry);
                                 if(success){
                                     System.out.println("The update was sucessful");
                                     
                                 }else{
                                     System.out.println("The update was not successful");
                                 }
                             
                         } else{ 
                             System.out.println("Please enter a valid number");
                         }
                     }
                      break;
                case 3:
                    input = new Scanner(System.in);
                    System.out.println("Enter the VIN number of the entry you want to remove");
                    String enterVIN = input.next();
                    Car check = pqMile.delMin(enterVIN);
                    Car checkTwo = pqPrice.delMin(enterVIN);
                    if(check == null && checkTwo == null){
                        System.out.println("The remove was successful");
                    }
                
                    break;
                case 4:
                    System.out.println("Car with the current lowest price: \n");
                    System.out.println(pqPrice.min());
                    break;
                case 5:
                    System.out.println("Car with the current lowest mileage: \n");
                    System.out.println(pqMile.min());
                    break;
                case 6:

                    input = new Scanner(System.in);
                    String findMake;
                    String findModel;

                    boolean found = false;
                    System.out.println("What model are you searching for?");
                    findModel = input.next();
                    System.out.println("What make are you searching for?");
                    findMake = input.next();

                    Car find = pqPrice.findLowest(findModel, findMake);
                    
                    if (find == null) {
                        System.out.println("Didn't return anything");

                    } else {
                        System.out.println(find);
                    }

                    break;
                case 7:
                    input = new Scanner(System.in);
                    String findMileMake;
                    String findMileModel;

                    System.out.println("What model are you searching for?");
                    findMileModel = input.next();
                    System.out.println("What make are you searching for?");
                    findMileMake = input.next();

                    Car mileFind;
                    mileFind = pqMile.findLowest(findMileModel, findMileMake);
                    
                    if (mileFind == null) {
                        System.out.println("Didn't return anything");

                    } else {
                        System.out.println(mileFind);
                    }
                    break;
                case 8:

                    break;
                default:
                    System.out.println("Please enter a valid menu choice");
                    menuChoice = 0;
                    break;
            }
            
        } while (menuChoice != 8);
        
    }
    
}
