
import java.io.*;
import java.util.*;
import java.net.*;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.ParserConfigurationException;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.xml.*;
import org.jdom.*;
import org.jdom.input.SAXBuilder;
import org.jdom.Document;
import org.jdom.Element;
import org.xml.sax.SAXException;
import java.util.List;

public class weatherSearch extends HttpServlet{
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        //request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html; charset=utf-8");
		String location = request.getParameter("location");
		String type = request.getParameter("type");
		String tempUnit = request.getParameter("tempUnit");
		PrintWriter out = response.getWriter();
		String url = "http://csci571hw8linghao-env.elasticbeanstalk.com/input.php";
		String query = url + "?location=" + URLEncoder.encode(location,"UTF-8") + "&type=" + type + "&tempUnit="+tempUnit;
		URL myUrl = new URL(query);
		URLConnection urlCon = myUrl.openConnection();
		urlCon.setAllowUserInteraction(false);
		InputStream urlStream = myUrl.openStream();
		BufferedReader in = new BufferedReader(new InputStreamReader(urlStream, "UTF-8"));
		BufferedReader debug = new BufferedReader(in);
		
		//
		//System.out.println("123");
		//
			SAXBuilder builder = new SAXBuilder();
        //System.out.println("1234566");
			String json = "{\"weather\":{";
			try{
				Document doc = builder.build(in);
				Element rootNode = doc.getRootElement();
				System.out.println(rootNode.getText());
				if(rootNode.getText().equals("NoResults")){
					String error = "NoResults";
					out.print(error);
					out.close();
					return;
				}
      		  //System.out.println("12345dd");
				//for forecast
				json += "\"forecast\":[";
				List forecast = rootNode.getChildren("forecast");
        		//System.out.println("123453df");
				for(int i = 0; i < forecast.size(); i++){
					Element node = (Element)forecast.get(i);
					json += "{";
					json += "\"text\":\"" + node.getAttributeValue("text") + "\",";
					json += "\"high\":" + node.getAttributeValue("high") + ",";
					json += "\"day\":\"" + node.getAttributeValue("day") + "\",";
					json += "\"low\":" + node.getAttributeValue("low");
					json += "}";
					if(i != forecast.size() - 1){
						json += ",";
					}
				}
				json += "],";

				Element condition = rootNode.getChild("condition");
			
				json += "\"condition\":{" + "\"text\":\"" + condition.getAttributeValue("text") + "\",\"temp\":" + condition.getAttributeValue("temp") + "},";
			
				//location
				Element place = rootNode.getChild("location");
			
				json += "\"location\":{" + "\"region\":\"" + place.getAttributeValue("region") + "\",\"country\":\"" + place.getAttributeValue("country")+ "\",\"city\":\"" + place.getAttributeValue("city") + "\"},";
			
				Element link = rootNode.getChild("link");
				//link
				json += "\"link\":\"" + link.getText() + "\",";
				//img
				Element img = rootNode.getChild("img");
				json += "\"img\":\"" + img.getText() + "\",";
			
				//feed
				Element feed = rootNode.getChild("feed");
				json += "\"feed\":\"" + feed.getText() + "\",";
			
				//unit
				Element units = rootNode.getChild("units");
				json += "\"units\":{\"temperature\":\"" + units.getAttributeValue("temperature") + "\"}";
			
				//end
				json +="}}";
				out.print(json);
				out.close();
			}catch(Exception e){
				//System.out.println(debug.read());
				System.out.println(e);
				out.print("NoResults");
				out.close();
			}
	}
}