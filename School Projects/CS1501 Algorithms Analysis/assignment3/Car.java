public class Car{
    String VIN;
    String make;
    String model;
    int price;
    int mileage;
    String color;
    
    public Car(String v, String carMake, String carModel, int amount, 
            int miles, String carColor){
        
        VIN = v;
        make = carMake;
        model = carModel;
        price = amount;
        mileage = miles;
        color = carColor;
    }
    public String getVIN(){
        return VIN;
    }
    public void setVIN(String v){
        VIN = v;
    }
    
    public String getMake(){
        return make;
    }
    
    public void setMake(String carMake){
        make = carMake;
    }
    
    public String getModel(){
        return model;
    }
    
    public void setModel(String carModel){
        model = carModel;
    }
    
    public int getPrice(){
        return price;
    }
    
    public void setPrice(int amount){
        price = amount;
    }
    
    public int getMiles(){
        return mileage;
    }
    
    public void setMiles(int mile){
        mileage = mile;
    }
    
    public String getColor(){
        return color;
    }
    
    public void setColor(String c){
        color = c;
    }
    
    public String toString(){
        return "VIN Number: " + VIN + "\n" +
                "Model: " + model + "\n" +
                "Make: " + make + "\n" +
                "Price: " + price + "\n" +
                "Mileage: " + mileage + "\n" +
                "Color: " + color + "\n";
    }
}

/*


 VIN = v;
        make = carMake;
        model = carModel;
        price = amount;
        mileage = miles;
        color 
*/
