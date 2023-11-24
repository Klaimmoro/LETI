package io.proj3ct.GrowGuardian.service;


import lombok.Data;
import org.springframework.beans.factory.annotation.Value;

@Data
public class chosenActivity {

    @Value("")
    String Activity = "";

    @Value("")
    String MusicGenre = null;

    @Value("")
    int Budget = 0;

    @Value("")
    int peopleCount = 0;

    @Value("")
    int ageCategory = 0;

    @Value("")
    String day = null;

    @Value("")
    String month = null;

    @Value("")
    String time = "";

    @Value("")
    int year = 0;

}


//System.out.println(doc);
//Elements links = doc.select("a[href]");
//for (Element link : links) {
//    System.out.println(link.attr("href"));
//    if (link.attr("href").contains("#schedule")) {
//        sendMessage(chatID, "https://afisha.yandex.ru/" + link.attr("href"));
//    }
//}
