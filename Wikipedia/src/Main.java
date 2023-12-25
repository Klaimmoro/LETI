import org.jsoup.Jsoup;
import org.jsoup.nodes.Element;
import org.apache.commons.io.IOUtils;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) throws IOException {

        System.out.println("Enter you wiki request");
        String request = getRequest();

        String response = getResponseFromWiki(request);

        parseWiki(response,request);




    }

    private static String getResponseFromWiki(String request) throws IOException {

        URL url = new URL("https://en.wikipedia.org/wiki/"+request);
        URLConnection con = url.openConnection();
        InputStream in = con.getInputStream();
        String encoding = con.getContentEncoding();
        encoding = encoding == null ? "UTF-8" : encoding;
        return IOUtils.toString(in, encoding);
    }

    private static String getRequest() {
        Scanner console = new Scanner(System.in);
        return console.nextLine();
    }

    private static void parseWiki(String response, String request) throws IOException {
        org.jsoup.nodes.Document document = Jsoup.parse(response, "wikipedia.org");
        Element WikiText = document.body();
        showResult(WikiText,request);
    }

    private static void showResult(Element wikiText, String request) throws IOException {
        System.out.println(wikiText.text());
        try {
            String url = "https://en.wikipedia.org/wiki/"+request;
            java.awt.Desktop.getDesktop().browse(java.net.URI.create(url));
        }
        catch (java.io.IOException e) {
            System.out.println(e.getMessage());
        }
    }
}