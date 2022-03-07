package il.co.ilrd.hashmap;

import java.util.Collection;
import java.util.Iterator;
import java.util.Set;
import java.util.Map.Entry;



public class TestHashMap {
    public static void main(String[] args) {
        Hashmap<Integer,String> myhash = new Hashmap<>(20);
        Hashmap<Integer,String> putallhash = new Hashmap<>(20);
        if (!myhash.isEmpty()){
            System.out.println("failed in isempty1");
        }

        if(myhash.size() != 0){
            System.out.println("failed in size1");
        }

        myhash.put(10, "almog");
        myhash.put(22, "andrey");
        myhash.put(30, "omer");

        if (myhash.isEmpty()){
            System.out.println("failed in isempty2");
        }

        if(myhash.size() != 3){
            System.out.println("failed in size2");
        }

        myhash.clear();

        if (!myhash.isEmpty()){
            System.out.println("failed in isempty3");
        }

        if(myhash.size() != 0){
            System.out.println("failed in size3");
        }

        myhash.put(10, "almog");
        myhash.put(22, "andrey");
        myhash.put(30, "omer");
        myhash.put(40, "idan");
        myhash.put(50, "maya");
        myhash.put(60, "eden");
        myhash.put(70, "shir");
        myhash.put(80, "hila");

        if(myhash.size() != 8){
            System.out.println("failed in size4");
        }

        if(!myhash.containsKey(50)){
            System.out.println("failed in containsKey1");
        }

        if(!myhash.containsValue("almog")){
            System.out.println("failed in containsValue1");
        }

        if(myhash.remove(80) != "hila" ){
            System.out.println("failed in remove1");
        }

        if(myhash.size() != 7){
            System.out.println("failed in size5");
        }

        if(myhash.containsKey(80)){
            System.out.println("failed in containsKey2");
        }

        if(myhash.containsValue("hila")){
            System.out.println("failed in containsValue2");
        }

        if(myhash.put(10, "almog2") != "almog"){
            System.out.println("failed in put");
        }

        if(myhash.get(10) != "almog2"){
            System.out.println("failed in get1");
        }
        if(myhash.get(22) != "andrey"){
            System.out.println("failed in get2");
        }
        if(myhash.get(30) != "omer"){
            System.out.println("failed in get3");
        }
        if(myhash.get(40) != "idan"){
            System.out.println("failed in get4");
        }
        
        if(myhash.get(50) != "maya"){
            System.out.println("failed in get5");
        }

        if(myhash.get(60) != "eden"){
            System.out.println("failed in get6");
        }

        if(myhash.get(70) != "shir"){
            System.out.println("failed in get7");
        }

        if(myhash.get(80) != null){
            System.out.println("failed in get8");
        }
        
        Set<Entry<Integer,String>> myset = myhash.entrySet();
        Iterator<Entry<Integer,String>> iter = myset.iterator();
        while(iter.hasNext()) {
            System.out.println(iter.next());
        }

        Set<Integer> keyset = myhash.keySet();
        Iterator<Integer> iterKey = keyset.iterator();
        while(iterKey.hasNext()) {
            System.out.println(iterKey.next());
        }


        Collection<String> values = myhash.values();
        Iterator<String> iterVal = values.iterator();
        while(iterVal.hasNext()) {
            System.out.println(iterVal.next());
        }

        putallhash.put(22, "hi");
        putallhash.put(40, "how");
        putallhash.put(65, "are");
        putallhash.put(88, "you");

        myhash.putAll(putallhash);
        Set<Entry<Integer,String>> myset1 = myhash.entrySet();
        Iterator<Entry<Integer,String>> iter1 = myset1.iterator();
        while(iter1.hasNext()) {
            System.out.println(iter1.next());
        }


        System.out.println("test done!");


    }
}
