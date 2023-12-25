

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

class Info {
    HashMap<String, Integer> repeats = new HashMap<>();

    void foo(String str)
    {
        String temp = "";
        temp = str.substring(0,str.length()-2);
        if (repeats.isEmpty()) {
            repeats.put(temp, 1);
            switch (str.charAt(str.length()-1)) {
                case '1':
                    fl1++;
                    break;
                    case '2':
                        fl2++;
                        break; case '3': fl3++;
                        break; case '4': fl4++;
                        break; case '5': fl5++;
                        break; default://ZAHAR boba <3
                    break;
            }
            return;
        }
        if (repeats.containsKey(temp))
            repeats.put(temp,repeats.get(temp) + 1);
        else
        {
            repeats.put(temp,1);
            switch (str.charAt(str.length()-1)) {
                case '1':
                    fl1++;
                    break;
                    case '2':
                        fl2++;
                        break; case '3': fl3++;
                        break; case '4': fl4++;
                        break; case '5': fl5++;
                        break; default://ZAHAR boba <3
                    break;
            }
            return;

        }


    }


    int fl1=0; int fl2=0; int fl3=0; int fl4=0; int fl5=0;
}

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner console = new Scanner(System.in);
        while(true) {
        String pathToCsv = console.nextLine();
        long time = System.currentTimeMillis();
        if(pathToCsv.contains("csv")) {
            BufferedReader csvReader = new BufferedReader(new FileReader(pathToCsv));
            String row;
            HashMap<String, Info> cityInfo = new HashMap<>();
            while ((row = csvReader.readLine()) != null) {
                if (row.contains("city")) continue;
                String key = "";
                int i = 0;
                while (row.charAt(i) != ';') {
                    key += row.charAt(i++);
                }
                row = row.replace(key + ';', "");
                if (!cityInfo.containsKey(key)) {
                    cityInfo.put(key, new Info());
                    cityInfo.get(key).foo(row);
                } else
                    cityInfo.get(key).foo(row);
            }
            System.out.println("Floor statistics");
            cityInfo.forEach((key, value) -> System.out.println(key + " " +
                    value.fl1 + " " + value.fl2 + " " + value.fl3 + " " + value.fl4 + " " + value.fl5 + " "));
            System.out.println("Repeat statistics");
            for (String name : cityInfo.keySet()) {
                String key = name.toString();
                String value = cityInfo.get(name).toString();
                for (String ads : cityInfo.get(name).repeats.keySet()) {
                    String key1 = ads.toString();
                    int value1 = cityInfo.get(name).repeats.get(key1);
                    if (value1 > 1) System.out.println(key + " " + key1 + " " + value1);
                }
            }

            csvReader.close();
        }

        if(pathToCsv.contains("XML")){
            BufferedReader xmlReader = new BufferedReader(new FileReader(pathToCsv));
            String row;
            HashMap<String, Info> cityInfo = new HashMap<>();
            //C:\Users\klaim\Downloads\address.XML
            while ((row = xmlReader.readLine()) != null) {
                if(row.contains("encoding") || row.contains("root")) continue;
                row = row.replace("<item city=", "");row = row.replace("street=", ";");row = row.replace("house=", ";");row = row.replace("floor=", ";");row = row.replace("/>", "");
                String key = "";
                int i = 0;
                while (row.charAt(i) != ';') {
                    key += row.charAt(i++);
                }
                row = row.replace(key + ';', "");
                row = row.substring(0,row.length()-2);
                if (!cityInfo.containsKey(key)) {
                    cityInfo.put(key, new Info());
                    cityInfo.get(key).foo(row);
                } else
                    cityInfo.get(key).foo(row);
            }

            System.out.println("Floor statistics");
            cityInfo.forEach((key, value) -> System.out.println(key + " " +
                    value.fl1 + " " + value.fl2 + " " + value.fl3 + " " + value.fl4 + " " + value.fl5 + " "));
            System.out.println("Repeat statistics");
            for (String name : cityInfo.keySet()) {
                String key = name.toString();
                String value = cityInfo.get(name).toString();
                for (String ads : cityInfo.get(name).repeats.keySet()) {
                    String key1 = ads.toString();
                    int value1 = cityInfo.get(name).repeats.get(key1);
                    if (value1 > 1) System.out.println(key + " " + key1 + " " + value1);
                }
            }
            xmlReader.close();
            }
        System.out.println("Work time:" + (System.currentTimeMillis() - time));
        String str = console.next();
        if("z".equals(str)) {
            break;
        }
        }
    }
}