package io.proj3ct.GrowGuardian.service;
import io.proj3ct.GrowGuardian.config.BotConfig;
import lombok.extern.slf4j.Slf4j;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.openqa.selenium.By;
import org.openqa.selenium.Cookie;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.springframework.stereotype.Component;
import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.methods.updatingmessages.EditMessageText;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.InlineKeyboardMarkup;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.buttons.InlineKeyboardButton;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;
import org.xml.sax.SAXException;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPathExpressionException;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

@Slf4j
@Component
public class TelegramBot extends TelegramLongPollingBot {

    cookies Cook = new cookies();

    public chosenActivity act = new chosenActivity();

    final BotConfig config;

    public WebDriver driver = new FirefoxDriver();

    String CallData = "";

    boolean StopUpdate = true;

    public TelegramBot(BotConfig config) { this.config =config; }

    @Override
    public String getBotToken(){
        return config.getBotToken();
    }

    @Override
    public String getBotUsername() {
        return config.getBotName();
    }

    @Override
    public void onUpdateReceived(Update update) {
        if(update.hasMessage() && update.getMessage().hasText()){
            String messagetext = update.getMessage().getText();
            long chatID = update.getMessage().getChatId();

            if (CallData.equals("Budget"))
            {
                act.setBudget(Integer.parseInt(messagetext));
                sendMessage(chatID,"Your budget is: " + String.valueOf(act.getBudget()));
                StopUpdate=true;
                CallData="";
            }

            if (CallData.equals("People"))
            {
                act.setPeopleCount(Integer.parseInt(messagetext));
                sendMessage(chatID,"Count of people is: " + String.valueOf(act.getPeopleCount()));
                StopUpdate=true;
                CallData="";
            }

            if (CallData.equals("Age"))
            {
                act.setAgeCategory(Integer.parseInt(messagetext));
                sendMessage(chatID,"Age category set to: " + String.valueOf(act.getAgeCategory()));
                StopUpdate=true;
                CallData="";
            }

            switch (messagetext){
                case "/start":
                    startCommandReceived(chatID,update.getMessage().getChat().getFirstName());
                    if(driver.findElement(By.xpath("/html/body/div/div[1]/div[2]/h1")).getText().equals("Авторизация не удалась")) {
                        //authorization();
                    }
                    else{
                        loadCookies();
                    }
                    break;
                case "/show":
                    try {
                        findActivityReceived(chatID);
                    } catch (IOException | ParserConfigurationException | SAXException | XPathExpressionException |
                             InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                    break;
                case "/activityParameters":
                    changeParameters(chatID);
                    break;
                default:
                    break;
            }
        }
        else if (update.hasCallbackQuery() && StopUpdate)
        {
            String callbackData = update.getCallbackQuery().getData();
            long messageId = update.getCallbackQuery().getMessage().getMessageId();
            long chatId = update.getCallbackQuery().getMessage().getChatId();
            EditMessageText message = new EditMessageText();

            if(callbackData.equals("Morning") || callbackData.equals("Afternoon") || callbackData.equals("Evening")){
                act.setTime(callbackData);
                sendMessage(chatId, "Your time is: " + act.getTime());
            }

            if(callbackData.equals("Culture") || callbackData.equals("Education") || callbackData.equals("Sport") || callbackData.equals("SkipTopic")) {
                if (callbackData.equals("SkipTopic"))
                    sendMessage(chatId, "Your topic is: Any");
                else {
                    act.setActivity(callbackData);
                    message.setText("Your topic is: " + act.getActivity());
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    message.setReplyMarkup(null);
                    exe(message);
                    changeParameters(chatId);
                }
            }

            if (callbackData.equals("Pop") || callbackData.equals("Rock") || callbackData.equals("Classical music") || callbackData.equals("Hip hop and rap") || callbackData.equals("Jazz and blues") || callbackData.equals("Indie") || callbackData.equals("Electronic music") ||  callbackData.equals("Chanson") || callbackData.equals("Stage") || callbackData.equals("Metal") || callbackData.equals("SkipGenre")) {
                if (callbackData.equals("SkipGenre"))
                {
                    act.setActivity("Music");
                    message.setText("Your topic is: Music \nYour genre is: Any");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    message.setReplyMarkup(null);
                    exe(message);
                    changeParameters(chatId);

                }
                else {
                    act.setMusicGenre(callbackData);
                    act.setActivity("Music");
                    message.setText("Your topic is: Music \nYour genre is: " + act.getMusicGenre());
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    message.setReplyMarkup(null);
                    exe(message);
                    changeParameters(chatId);

                }
            }

            if(callbackData.equals("1") || callbackData.equals("3") || callbackData.equals("5") || callbackData.equals("7") || callbackData.equals("8") || callbackData.equals("10") || callbackData.equals("12")){
                act.setMonth(callbackData);
                message.setText("Choose day");
                message.setChatId(String.valueOf(chatId));
                message.setMessageId((int) messageId);
                days(31, message);

            }

            if(callbackData.equals("4") || callbackData.equals("6") || callbackData.equals("9") || callbackData.equals("11")){
                act.setMonth(callbackData);
                message.setText("Choose day");
                message.setChatId(String.valueOf(chatId));
                message.setMessageId((int)messageId);
                days(30,message);
            }

            if(callbackData.equals("2")){
                act.setMonth(callbackData);
                message.setText("Choose day");
                message.setChatId(String.valueOf(chatId));
                message.setMessageId((int)messageId);
                days(28,message);
            }

            //if (callbackData.equals("SkipMonth"))                             переделать под пересчет всего месяца
            //{
            //    act.setMonth("");
            //    message.setText("Choose day");
            //    message.setChatId(String.valueOf(chatId));
            //    message.setMessageId((int) messageId);
            //    days(31, message);
            //}
//
            //if (callbackData.equals("SkipDay"))
            //{
            //    sendMessage(chatId,"Your date is: any month and any day");
            //}

            if(callbackData.contains("Day")){
                act.setDay(callbackData.substring(3));
                //sendMessage(chatId,"Your date is: " + act.day + ' ' + act.month);
                message.setText("Your date is: " + act.day + ' ' + act.month);
                message.setChatId(String.valueOf(chatId));
                message.setMessageId((int)messageId);
                message.setReplyMarkup(null);
                exe(message);
                changeParameters(chatId);
            }

            switch(callbackData)
            {
                case "Topic":
                    message.setText("Choose your topic");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    setActivityTopic(update,message);
                    break;

                case "Time":
                    message.setText("Choose your time");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    time(update,message);
                    break;

                case "Budget":
                    message.setText("Enter your budget");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    StopUpdate = false;
                    CallData = "Budget";
                    exe(message);
                    break;

                case "People":
                    message.setText("Enter count of people");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    StopUpdate = false;
                    CallData = "People";
                    exe(message);
                    break;

                case "Age":
                    message.setText("Enter age category");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    StopUpdate = false;
                    CallData = "Age";
                    exe(message);
                    break;

                case "Date":
                    message.setText("Enter date of activity");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    createCalendar(message);
                    break;
                case "Music":
                    message.setText("Choose your genre");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    setMusicStyle(update,message);
                    break;

                case "SkipAll":
                    message.setText("That's all your parametrs");
                    message.setChatId(String.valueOf(chatId));
                    message.setMessageId((int)messageId);
                    message.setReplyMarkup(null);
                    exe(message);
                    break;

                default:
                    break;

            }


        }
    }

    public void time(Update update,EditMessageText message){
        InlineKeyboardMarkup markupInLine = new InlineKeyboardMarkup();
        List<List<InlineKeyboardButton>> rowsInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine = new ArrayList<>();

        var MorningButton = new InlineKeyboardButton();
        MorningButton.setText("Morning (6-12 AM)");
        MorningButton.setCallbackData("Morning");

        var AfternoonButton = new InlineKeyboardButton();
        AfternoonButton.setText("Afternoon (12-18 PM)");
        AfternoonButton.setCallbackData("Afternoon");

        var EveningButton = new InlineKeyboardButton();
        EveningButton.setText("Evening (18-24 PM)");
        EveningButton.setCallbackData("Evening");


        rowInLine.add(MorningButton);
        rowInLine.add(AfternoonButton);
        rowInLine.add(EveningButton);
        rowsInLine.add(rowInLine);
        markupInLine.setKeyboard(rowsInLine);
        message.setReplyMarkup(markupInLine);


        exe(message);


    }

    public void days(int daysCount, EditMessageText message)
    {
        InlineKeyboardMarkup markupInLine = new InlineKeyboardMarkup();
        List<List<InlineKeyboardButton>> rowsInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine1 = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine2 = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine3 = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine4 = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine5 = new ArrayList<>();
        //List<InlineKeyboardButton> skipList = new ArrayList<>();


        for (int i = 1; i <= daysCount; i++)
        {
            var qwe = new InlineKeyboardButton();
            qwe.setText(String.valueOf(i));
            qwe.setCallbackData("Day" + i);
            if (i <= 7)
                rowInLine1.add(qwe);
            else if (i <= 14)
                rowInLine2.add(qwe);
            else if (i <= 21)
                rowInLine3.add(qwe);
            else if (i <= 28)
                rowInLine4.add(qwe);
            else if (i <= 31)
                rowInLine5.add(qwe);

        }

        var SkipButton = new InlineKeyboardButton();
        SkipButton.setText("Any");
        SkipButton.setCallbackData("SkipDay");

        //skipList.add(SkipButton);
        //rowsInLine.add(skipList);


        rowsInLine.add(rowInLine1);rowsInLine.add(rowInLine2);rowsInLine.add(rowInLine3);rowsInLine.add(rowInLine4);rowsInLine.add(rowInLine5);

        markupInLine.setKeyboard(rowsInLine);
        message.setReplyMarkup(markupInLine);

        exe(message);
    }
    public void createCalendar(EditMessageText message){
        InlineKeyboardMarkup markupInLine = new InlineKeyboardMarkup();
        List<List<InlineKeyboardButton>> rowsInLine = new ArrayList<>();
        List<InlineKeyboardButton> Summer = new ArrayList<>();
        List<InlineKeyboardButton> Winter = new ArrayList<>();
        List<InlineKeyboardButton> Autumn = new ArrayList<>();
        List<InlineKeyboardButton> Spring = new ArrayList<>();
        //List<InlineKeyboardButton> skipList = new ArrayList<>();

        var January = new InlineKeyboardButton();
        January.setText("January");
        January.setCallbackData("1");

        var February = new InlineKeyboardButton();
        February.setText("February");
        February.setCallbackData("2");

        var March = new InlineKeyboardButton();
        March.setText("March");
        March.setCallbackData("3");

        var April = new InlineKeyboardButton();
        April.setText("April");
        April.setCallbackData("4");

        var May = new InlineKeyboardButton();
        May.setText("May");
        May.setCallbackData("5");

        var June = new InlineKeyboardButton();
        June.setText("June");
        June.setCallbackData("6");

        var July = new InlineKeyboardButton();
        July.setText("July");
        July.setCallbackData("7");

        var August = new InlineKeyboardButton();
        August.setText("August");
        August.setCallbackData("8");

        var September = new InlineKeyboardButton();
        September.setText("September");
        September.setCallbackData("9");

        var October = new InlineKeyboardButton();
        October.setText("October");
        October.setCallbackData("10");

        var November = new InlineKeyboardButton();
        November.setText("November");
        November.setCallbackData("11");

        var December = new InlineKeyboardButton();
        December.setText("December");
        December.setCallbackData("12");

        var SkipButton = new InlineKeyboardButton();
        SkipButton.setText("Any");
        SkipButton.setCallbackData("SkipMonth");

        //skipList.add(SkipButton);

        Winter.add(December); Winter.add(January); Winter.add(February);

        Spring.add(March); Spring.add(April); Spring.add(May);

        Summer.add(June); Summer.add(July); Summer.add(August);

        Autumn.add(September); Autumn.add(October); Autumn.add(November);

        rowsInLine.add(Winter); rowsInLine.add(Spring); rowsInLine.add(Summer); rowsInLine.add(Autumn);

        //rowsInLine.add(skipList);

        markupInLine.setKeyboard(rowsInLine);
        message.setReplyMarkup(markupInLine);

        exe(message);

    }

    public void setMusicStyle(Update update,EditMessageText message)
    {
        InlineKeyboardMarkup markupInLine = new InlineKeyboardMarkup();
        List<List<InlineKeyboardButton>> rowsInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine2 = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine3 = new ArrayList<>();
        //List<InlineKeyboardButton> rowInLine4 = new ArrayList<>();
        List<InlineKeyboardButton> skipList = new ArrayList<>();

        var PopButton = new InlineKeyboardButton();
        PopButton.setText("Pop");
        PopButton.setCallbackData("Pop");

        var RockButton = new InlineKeyboardButton();
        RockButton.setText("Rock");
        RockButton.setCallbackData("Rock");

        var ClassicalButton = new InlineKeyboardButton();
        ClassicalButton.setText("Classical music");
        ClassicalButton.setCallbackData("Classical music");

        var HipButton = new InlineKeyboardButton();
        HipButton.setText("Hiphop and Rap");
        HipButton.setCallbackData("Hiphop and rap");

        var JazzButton = new InlineKeyboardButton();
        JazzButton.setText("Jazz and Blues");
        JazzButton.setCallbackData("Jazz and blues");

        var IndieButton = new InlineKeyboardButton();
        IndieButton.setText("Indie");
        IndieButton.setCallbackData("Indie");

        var ElectronicButton = new InlineKeyboardButton();
        ElectronicButton.setText("Electronic music");
        ElectronicButton.setCallbackData("Electronic music");

        var ChansonButton = new InlineKeyboardButton();
        ChansonButton.setText("Chanson");
        ChansonButton.setCallbackData("Chanson");

        var StageButton = new InlineKeyboardButton();
        StageButton.setText("Stage");
        StageButton.setCallbackData("Stage");

        var MetalButton = new InlineKeyboardButton();
        MetalButton.setText("Metal");
        MetalButton.setCallbackData("Metal");

        var SkipButton = new InlineKeyboardButton();
        SkipButton.setText("Any");
        SkipButton.setCallbackData("SkipGenre");



        rowInLine.add(PopButton);
        rowInLine.add(ChansonButton);
        rowInLine.add(ClassicalButton);
        rowsInLine.add(rowInLine);

        rowInLine2.add(JazzButton);
        rowInLine2.add(IndieButton);
        rowInLine2.add(StageButton);
        rowsInLine.add(rowInLine2);

        rowInLine3.add(RockButton);
        rowInLine3.add(ElectronicButton);
        rowInLine3.add(MetalButton);
        rowsInLine.add(rowInLine3);

        skipList.add(HipButton);
        skipList.add(SkipButton);

        rowsInLine.add(skipList);

        markupInLine.setKeyboard(rowsInLine);
        message.setReplyMarkup(markupInLine);

        exe(message);

        //act.setActivity(update.getCallbackQuery().getData());                                             ???????????

    }
    public void setActivityTopic(Update update,EditMessageText message) {

        InlineKeyboardMarkup markupInLine = new InlineKeyboardMarkup();
        List<List<InlineKeyboardButton>> rowsInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine2 = new ArrayList<>();
        List<InlineKeyboardButton> skipList = new ArrayList<>();

        var CultButton = new InlineKeyboardButton();
        CultButton.setText("Culture");
        CultButton.setCallbackData("Culture");

        var SportButton = new InlineKeyboardButton();
        SportButton.setText("Sport");
        SportButton.setCallbackData("Sport");

        var EducButton = new InlineKeyboardButton();
        EducButton.setText("Education");
        EducButton.setCallbackData("Education");

        var MusicButton = new InlineKeyboardButton();
        MusicButton.setText("Music");
        MusicButton.setCallbackData("Music");

        var SkipButton = new InlineKeyboardButton();
        SkipButton.setText("Any");
        SkipButton.setCallbackData("SkipTopic");


        rowInLine.add(CultButton);
        rowInLine.add(SportButton);
        rowsInLine.add(rowInLine);

        rowInLine2.add(EducButton);
        rowInLine2.add(MusicButton);
        rowsInLine.add(rowInLine2);


        skipList.add(SkipButton);

        rowsInLine.add(skipList);

        markupInLine.setKeyboard(rowsInLine);
        message.setReplyMarkup(markupInLine);

        exe(message);

        act.setActivity(update.getCallbackQuery().getData());

    }

    private void changeParameters(long chatID)
    {

        SendMessage message = new SendMessage();
        message.setChatId(String.valueOf(chatID));
        message.setText("Select category to change");

        InlineKeyboardMarkup markupInLine = new InlineKeyboardMarkup();
        List<List<InlineKeyboardButton>> rowsInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine2 = new ArrayList<>();
        List<InlineKeyboardButton> rowInLine3= new ArrayList<>();
        List<InlineKeyboardButton> skipList = new ArrayList<>();

        var TopicButton = new InlineKeyboardButton();
        TopicButton.setText("Topic");
        TopicButton.setCallbackData("Topic");

        var BudgetButton = new InlineKeyboardButton();
        BudgetButton.setText("Budget");
        BudgetButton.setCallbackData("Budget");

        var PeopleButton = new InlineKeyboardButton();
        PeopleButton.setText("Count of people");
        PeopleButton.setCallbackData("People");

        var AgeButton = new InlineKeyboardButton();
        AgeButton.setText("Age category");
        AgeButton.setCallbackData("Age");

        var DateButton = new InlineKeyboardButton();
        DateButton.setText("Date");
        DateButton.setCallbackData("Date");

        var TimeButton = new InlineKeyboardButton();
        TimeButton.setText("Time");
        TimeButton.setCallbackData("Time");

        var SkipButton = new InlineKeyboardButton();
        SkipButton.setText("Any/End");
        SkipButton.setCallbackData("SkipAll");

        rowInLine.add(TopicButton);
        rowInLine.add(BudgetButton);
        rowsInLine.add(rowInLine);

        rowInLine2.add(PeopleButton);
        rowInLine2.add(AgeButton);
        rowsInLine.add(rowInLine2);

        rowInLine3.add(DateButton);
        rowInLine3.add(TimeButton);
        rowsInLine.add(rowInLine3);

        skipList.add(SkipButton);
        rowsInLine.add(skipList);
        markupInLine.setKeyboard(rowsInLine);
        message.setReplyMarkup(markupInLine);

        exe(message);


    }

    public void loadCookies(){
        System.setProperty("webdriver.gecko.driver","C:\\Users\\klaim\\Desktop\\'ЛЭТИ'\\Kotlin\\GrowGuardian\\drivers\\geckodriver.exe");
        driver.manage().deleteAllCookies();
        driver.get("https://afisha.yandex.ru/saint-petersburg?rubric=cinema");
        driver.manage().addCookie(Cook.sessar);
        driver.manage().addCookie(Cook.is_gdpr);
        driver.manage().addCookie(Cook.yashr);
        driver.manage().addCookie(Cook._yasc);
        driver.manage().addCookie(Cook.i);
        driver.manage().addCookie(Cook._csrf);
        driver.manage().addCookie(Cook.yuidss);
        driver.manage().addCookie(Cook._ym_d);
        driver.manage().addCookie(Cook.L);
        driver.manage().addCookie(Cook.afisha_sid);
        driver.manage().addCookie(Cook._ym_visorc);
        driver.manage().addCookie(Cook.sessionid2);
        driver.manage().addCookie(Cook.gdpr);
        driver.manage().addCookie(Cook._ym_uid);
        driver.manage().addCookie(Cook.yandex_login);
        driver.manage().addCookie(Cook.is_gdpr_b);
        driver.manage().addCookie(Cook.yp);
        driver.manage().addCookie(Cook._ym_isad);
        driver.manage().addCookie(Cook.Session_id);
        driver.manage().addCookie(Cook.yandexuid);
        driver.manage().addCookie(Cook.ymex);
        //driver.get("https://afisha.yandex.ru/saint-petersburg");
        driver.navigate().refresh();
    }

    private void findActivityReceived(long chatID) throws IOException, ParserConfigurationException, SAXException, XPathExpressionException, InterruptedException {

        String urlcore = "https://afisha.yandex.ru/saint-petersburg?";
        ArrayList<String> activity = new ArrayList<>();
        ArrayList<String> filter = new ArrayList<>();


        if (act.day != null && act.month != null) {
            urlcore += "date=2023-" + act.month + "-" + act.day;
        }



        if (act.Activity.equals("Culture"))
        {
            activity.add("&rubric=cinema");
            activity.add("&rubric=theatre");
            activity.add("&rubric=art");
        }
        if (act.Activity.equals("Sport"))
        {
            activity.add("&rubric=sport");
        }
        if (act.Activity.equals("Education"))
        {
            activity.add("&rubric=excursions");
            activity.add("&rubric=art");
        }
        if (act.Activity.equals("Music"))
        {
            activity.add("&rubric=concert");
        }

        if (act.getMusicGenre() != null) {
            switch (act.MusicGenre) {
                case "Pop":
                    filter.add("&filter=pop");
                case "Rock":
                    filter.add("&filter=rock");
                case "Classical music":
                    filter.add("&filter=classical_music");
                case "Hiphop and rap":
                    filter.add("&filter=hiphop");
                case "Jazz and blues":
                    filter.add("&filter=jazz-blues");
                case "Indie":
                    filter.add("&filter=indie");
                case "Electronic music":
                    filter.add("&filter=electronic");
                case "Chanson":
                    filter.add("&filter=chanson");
                case "Stage":
                    filter.add("&filter=estrada");
                case "Metal":
                    filter.add("&filter=metal");
                default:
                    break;
            }
        }
        while(!activity.isEmpty()) {
            String url = urlcore;
            url += activity.get(activity.size()-1);
            if (act.Activity.equals("Music") && !filter.isEmpty())
            {
                url+= filter.get(activity.size()-1);
            }
            activity.remove(activity.size()-1);
            driver.get(url);


            String html = driver.getPageSource();
            Document doc = Jsoup.parse(html);
            //Document doc = Jsoup.connect("https://afisha.yandex.ru/saint-petersburg?rubric=cinema").get();
            Elements elem = doc.selectXpath("/html/body/div[2]/div[3]/div/div/div[2]/main/div[2]/div/div/div[3]");
            // /html/body/div[2]/div[3]/div/div/div[2]/main[2]/div[2]/div/div/div[3]
            for (Element element : elem.select("a")) {
                if (element.attr("href").contains("#schedule")) {
                    sendMessage(chatID, "https://afisha.yandex.ru" + element.attr("href"));
                }
            }
        }

    }

    private void exe(SendMessage message)
    {
        try {
            execute(message);
        } catch (TelegramApiException e) {
            log.error("Error occured" + e.getMessage());
        }
    }

    private void exe(EditMessageText message)
    {
        try {
            execute(message);
        } catch (TelegramApiException e) {
            log.error("Error occured" + e.getMessage());
        }
    }

    private void startCommandReceived(long chatID, String firstName){
        String answer = "Hi, " + firstName + ", nice to meet you!";
        sendMessage(chatID, answer);
        log.info("Replied to user " + firstName);
    }

    private void sendMessage(long chatID, String textToSend){
        SendMessage message = new SendMessage();
        message.setChatId(String.valueOf(chatID));
        message.setText(textToSend);

        exe(message);
    }

    public void authorization() throws InterruptedException {
        System.setProperty("webdriver.gecko.driver","C:\\Users\\DELL\\Desktop\\Новая папка (2)\\GrowGuardian\\drivers\\geckodriver.exe");
        driver.get("https://passport.yandex.ru/auth/welcome?origin=afisha&retpath=https%3A%2F%2Fafisha.yandex.ru%2Fsaint-petersburg");
        driver.findElement(By.xpath("//*[@id=\"passp-field-login\"]")).sendKeys("zakhar.vorzhev@yandex.ru");
        Thread.sleep(5000);
        driver.findElement(By.xpath("//*[@id=\"passp:sign-in\"]")).click();
        driver.findElement(By.xpath("//*[@id=\"passp-field-passwd\"]")).sendKeys("kEKLOL1337");
        Thread.sleep(5000);
        driver.findElement(By.xpath("//*[@id=\"passp:sign-in\"]")).click();

        Cook.sessar = driver.manage().getCookieNamed("sessar");

        Cook.is_gdpr = driver.manage().getCookieNamed("is_gdpr");

        Cook.yashr = driver.manage().getCookieNamed("yashr");

        Cook._yasc = driver.manage().getCookieNamed("yashr");

        Cook.i = driver.manage().getCookieNamed("i");

        Cook._csrf = driver.manage().getCookieNamed("_csrf");

        Cook.yuidss = driver.manage().getCookieNamed("yuidss");

        Cook._ym_d = driver.manage().getCookieNamed("_ym_d");

        Cook.L = driver.manage().getCookieNamed("L");

        Cook.afisha_sid = driver.manage().getCookieNamed("afisha_sid");

        Cook._ym_visorc = driver.manage().getCookieNamed("_ym_visorc");

        Cook.sessionid2 = driver.manage().getCookieNamed("sessionid2");

        Cook.gdpr = driver.manage().getCookieNamed("gdpr");

        Cook._ym_uid = driver.manage().getCookieNamed("_ym_uid");

        Cook.yandex_login = driver.manage().getCookieNamed("yandex_login");

        Cook.is_gdpr_b = driver.manage().getCookieNamed("is_gdpr_b");

        Cook.yp = driver.manage().getCookieNamed("yp");

        Cook._ym_isad = driver.manage().getCookieNamed("_ym_isad");

        Cook.Session_id = driver.manage().getCookieNamed("Session_id");

        Cook.yandexuid = driver.manage().getCookieNamed("yandexuid");

        Cook.ymex = driver.manage().getCookieNamed("ymex");

        /*java.util.concurrent.TimeUnit.SECONDS.sleep(20);
        File file = new File("C:\\Users\\klaim\\Desktop\\'ЛЭТИ'\\Kotlin\\GrowGuardian\\Cookies\\Cookies.data");
        try
        {
            file.delete();
            file.createNewFile();
            FileWriter fileWrite = new FileWriter(file);
            BufferedWriter Bwrite = new BufferedWriter(fileWrite);
            for(Cookie ck : driver.manage().getCookies())
            {
                Bwrite.write((ck.getName()+";"+ck.getValue()+";"+ck.getDomain()+";"+ck.getPath()+";"+ck.getExpiry()+";"+ck.isSecure()));
                Bwrite.newLine();
            }
            Bwrite.close();
            fileWrite.close();

        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }*/
    }


}
