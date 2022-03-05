package il.co.ilrd.collection;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class ObjectData{
    public String code;
    public int value;

    public ObjectData(String code, int value){
        this.code = code;
        this.value = value;
    }
}

public class Collection {
    public static void main(String[] args) {
        Integer[] array = new Integer[] { 1, 2, 9, 70, 21, 97 };
        System.out.println(Arrays.toString(array));
        List<Integer> list = Arrays.asList(array);
        Collections.sort(list);
        System.out.println(list);
        

        Map<String, Integer> days = new HashMap<>();
        days.put("sun", 1);
        days.put("mon", 2);
        days.put("tue", 3);
        days.put("wen", 4);
        days.put("thu", 5);
        days.put("fri", 6);
        days.put("sat", 7);

        for (Map.Entry<String, Integer> set : days.entrySet()) {
            System.out.println(set.toString());
        }

        for (Map.Entry<String, Integer> set : days.entrySet()) {
            System.out.println(set.getValue());
        }

        ObjectData o1 = new ObjectData("hello", 1);
        ObjectData o2 = new ObjectData("hello", 2);
        ObjectData o3 = new ObjectData("my", 3);
        ObjectData o4 = new ObjectData("my", 4);
        ObjectData o5 = new ObjectData("name", 5);
        ObjectData[] arr = new ObjectData[]{o1,o2,o3,o4,o5};

        Map<String, Integer> m = new HashMap<>();
        for (ObjectData element : arr) {
            String code = element.code;
            int value = element.value;
            if(m.containsKey(code)){
                value += m.get(code);
            }

            m.put(code, value);
        }
        
        for (Map.Entry<String, Integer> set : m.entrySet()) {
            System.out.println(set.toString());
        }
    }




}
