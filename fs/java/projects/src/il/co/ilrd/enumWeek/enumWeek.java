package il.co.ilrd.enumWeek;

public class enumWeek {
    public enum EWeekDay{
        SUNDAY,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY;

        public int getValue() {
            return ordinal();
        }

        public static EWeekDay fromValue(int index) {
            return EWeekDay.values()[index];
        }

        public static void printValues() {
            
            for(EWeekDay item : EWeekDay.values()){
                System.out.println(item);
            }   
            
        }
    }
    
    public static void main(String[] args)
    {
        EWeekDay d1 = EWeekDay.MONDAY;
        EWeekDay d5 = EWeekDay.FRIDAY;
        System.out.println("index of monday is: " + d1.getValue());
        System.out.println("index of friday is: " + d5.getValue());
        System.out.println("value of monday is: " + EWeekDay.fromValue(1));
        System.out.println("value of friday is: " + EWeekDay.fromValue(5));
        EWeekDay.printValues();
    }
}




