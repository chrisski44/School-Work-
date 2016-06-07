import java.util.Comparator;

class PricePriority<Object> implements Comparator<Object> {
    public int compare(Object one, Object two){
        
        Car carOne = (Car)one;
        Car carTwo = (Car)two;
        
        return Integer.compare(carOne.getPrice(), carTwo.getPrice());
    }
}
