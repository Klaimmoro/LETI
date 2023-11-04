package io.proj3ct.GrowGuardian.service;
import io.proj3ct.GrowGuardian.config.BotConfig;
import lombok.extern.slf4j.Slf4j;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
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
import org.jsoup.Jsoup;
import java.util.ArrayList;
import java.util.List;

@Slf4j
@Component
public class TelegramBot extends TelegramLongPollingBot {

    public chosenActivity act = new chosenActivity();
    final BotConfig config;

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
                    break;
                case "/show":
                    try {
                        findActivityReceived(chatID);
                    } catch (IOException | ParserConfigurationException | SAXException | XPathExpressionException e) {
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

            if(callbackData.equals("Culture") || callbackData.equals("Education") || callbackData.equals("Music") || callbackData.equals("Sport") || callbackData.equals("Skip")){
                act.setActivity(callbackData);
                sendMessage(chatId, "Your activity is: " + act.getActivity());
            }

            if(callbackData.equals("January") || callbackData.equals("March") || callbackData.equals("May") || callbackData.equals("July") || callbackData.equals("August") || callbackData.equals("October") || callbackData.equals("December")){
                act.setMonth(callbackData);
                message.setText("Choose day");
                message.setChatId(String.valueOf(chatId));
                message.setMessageId((int)messageId);
                days(31,message);
            }

            if(callbackData.equals("April") || callbackData.equals("June") || callbackData.equals("September") || callbackData.equals("November")){
                act.setMonth(callbackData);
                message.setText("Choose day");
                message.setChatId(String.valueOf(chatId));
                message.setMessageId((int)messageId);
                days(30,message);
            }

            if(callbackData.equals("February")){
                act.setMonth(callbackData);
                message.setText("Choose day");
                message.setChatId(String.valueOf(chatId));
                message.setMessageId((int)messageId);
                days(28,message);
            }

            if(callbackData.contains("Day")){
                act.setDay(callbackData.substring(3));
                sendMessage(chatId,"Your date is: " + act.day + ' ' + act.month);
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

                case "Skip":
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
        List<InlineKeyboardButton> skipList = new ArrayList<>();

        var January = new InlineKeyboardButton();
        January.setText("January");
        January.setCallbackData("January");

        var February = new InlineKeyboardButton();
        February.setText("February");
        February.setCallbackData("February");

        var March = new InlineKeyboardButton();
        March.setText("March");
        March.setCallbackData("March");

        var April = new InlineKeyboardButton();
        April.setText("April");
        April.setCallbackData("April");

        var May = new InlineKeyboardButton();
        May.setText("May");
        May.setCallbackData("May");

        var June = new InlineKeyboardButton();
        June.setText("June");
        June.setCallbackData("June");

        var July = new InlineKeyboardButton();
        July.setText("July");
        July.setCallbackData("July");

        var August = new InlineKeyboardButton();
        August.setText("August");
        August.setCallbackData("August");

        var September = new InlineKeyboardButton();
        September.setText("September");
        September.setCallbackData("September");

        var October = new InlineKeyboardButton();
        October.setText("October");
        October.setCallbackData("October");

        var November = new InlineKeyboardButton();
        November.setText("November");
        November.setCallbackData("November");

        var December = new InlineKeyboardButton();
        December.setText("December");
        December.setCallbackData("December");

        var SkipButton = new InlineKeyboardButton();
        SkipButton.setText("Skip");
        SkipButton.setCallbackData("Skip");

        skipList.add(SkipButton);

        Winter.add(December); Winter.add(January); Winter.add(February);

        Spring.add(March); Spring.add(April); Spring.add(May);

        Summer.add(June); Summer.add(July); Summer.add(August);

        Autumn.add(September); Autumn.add(October); Autumn.add(November);

        rowsInLine.add(Winter); rowsInLine.add(Spring); rowsInLine.add(Summer); rowsInLine.add(Autumn);

        rowsInLine.add(skipList);

        markupInLine.setKeyboard(rowsInLine);
        message.setReplyMarkup(markupInLine);

        exe(message);

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
        SkipButton.setText("Skip");
        SkipButton.setCallbackData("Skip");


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
        SkipButton.setText("Skip");
        SkipButton.setCallbackData("Skip");

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
    private void findActivityReceived(long chatID) throws IOException, ParserConfigurationException, SAXException, XPathExpressionException {
        System.setProperty("webdriver.gecko.driver","C:\\Users\\klaim\\Desktop\\'ЛЭТИ'\\Kotlin\\GrowGuardian\\drivers\\geckodriver.exe");

        WebDriver driver = new FirefoxDriver();
        driver.get("https://afisha.yandex.ru/saint-petersburg");
        String html = driver.getPageSource();
        Document doc = Jsoup.parse(html);

        System.out.println(doc);
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


}
