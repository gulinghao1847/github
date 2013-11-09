<?php
	$numOfWoeid = 1; 
	function getRet($value){
		$value = ($value=="")?"N/A":$value;
		return $value;
	}

	function display($woeid){
		$url = array();
		$weathers = array();
		
		$type = $GLOBALS["type"];
		$location = $GLOBALS["location"];
		$tempUnit = $GLOBALS["tempUnit"];
		$numOfWoeid = $GLOBALS["numOfWoeid"];
	
		for($i = 0; $i<$numOfWoeid;$i++){
			if($tempUnit == "F"){
				$unit="f";
			}else if($tempUnit == "C"){
				$unit="c";
			}
			$url[$i]="http://weather.yahooapis.com/forecastrss?w=".$woeid[$i]."&u=".$unit;
			$weathers[$i] = simplexml_load_file(urlencode($url[$i]),'SimpleXMLElement',LIBXML_NOCDATA);
		}

		$city = "N/A";
		$region = "N/A";
		$country = "N/A";
		$unit = "N/A";
		$lat = "N/A";
		$long = "N/A";
		$text = "N/A";
		$temp = "N/A";
		$imgSrc = "N/A";
		$link = "N/A";
				
		foreach($weathers as $weather){
			if($weather->channel->title == "Yahoo! Weather - Error"){
				$i--;
			}
		}

		//every xml   root = rss
		foreach($weathers as $weather){
			$day = array();
			$date = array();
			$low = array();
			$high = array();
			$textInfo = array();
			$code = array();
			
			
			if($weather->channel->title == "Yahoo! Weather - Error"){
				continue;
			}
		
			$simple=$weather;
			$simple->registerXPathNamespace('c', 'http://xml.weather.yahoo.com/ns/rss/1.0');
			$result = $simple->xpath('//c:location');
	
			foreach($result as $location){
				$city = getRet($location[@city]);
				$region = getRet($location[@region]);
				$country = getRet($location[@country]);
			}		
	
			$result = $simple->xpath('//c:units');
			foreach($result as $units){
				$unit = getRet($units[@temperature]);
			}
	
			$result = $simple->xpath('//c:condition');
			foreach($result as $condition){
				$text = getRet($condition[@text]);
				$temp = getRet($condition[@temp]);
			}	
			
			$i = 0;
			$result = $simple->xpath('//c:forecast');
			foreach($result as $forecast){
				$day[$i] = getRet($forecast[@day]);
				$date[$i] = getRet($forecast[@date]);
				$low[$i] = getRet($forecast[@low]);
				$high[$i] = getRet($forecast[@high]);
				$textInfo[$i] = getRet($forecast[@text]);
				$code[$i] = getRet($forecast[@code]);
				$i++;
			}
			//xpath =  http://www.w3.org/2003/01/geo/wgs84_pos#;
			$simple->registerXPathNamespace('d', 'http://www.w3.org/2003/01/geo/wgs84_pos#');
			$result = $simple->xpath('//d:lat');
			foreach($result as $lat){
				$lat = getRet($lat);
			}
	
			$result = $simple->xpath('//d:long');
			foreach($result as $long){
				$long = getRet($long);
			}
			$ele = $weather->channel->item->description;

			preg_match("/img src=(\"([^\"]*)\")/i", $ele, $matches);
			$imgSrc = $matches[0];
			$imgSrc = str_replace('img src=', '', $imgSrc);
			$imgSrc = str_replace('"', '', $imgSrc);
		
			preg_match("/a href=(\"([^\"]*)\")/i", $ele, $matches);
			$link = getRet($matches[0]);
			$link = str_replace('a href=', '', $link);
			$link = str_replace('"', '', $link);
			
			//echo
			$url[0] = urlencode($url[0]);
			echo "<weather>getResults";
			echo "<feed>" .$url[0]. "</feed>";
			echo "<link>".$link."</link>";
			echo "<location city = \"".$city."\" region = \"".$region."\" country = \"".$country."\"/>";
			echo "<units temperature = \"".$unit."\"/>";
			echo "<condition text = \"".$text."\" temp = \"".$temp."\"/>";
			echo "<img>".$imgSrc."</img>";
			for($idx = 0; $idx < $i; $idx++){
				echo "<forecast day=\"".$day[$idx]."\" low=\"".$low[$idx]."\" high=\"".$high[$idx]."\" text=\"".$textInfo[$idx]."\"/>";
			}
			echo "</weather>";
		}//end of for loop
	}//end of function display
		
			$location=$_GET["location"];
			$type=$_GET["type"];
			$tempUnit=(isset($_GET["tempUnit"]))?($_GET["tempUnit"]):"F";
				
			$url = "http://where.yahooapis.com/v1";
			$appid = "appid=<kqxeBVXV34HXPYn5mKYxxi8EXJNkx97l_2mE9G3uY_RX8wENwOk4qrxYRhWKf6xBLgDgzg-->";
			
			if($type == "city"){
				$url = "http://where.yahooapis.com/v1/places\$and(.q('".$location."'),.type(7));start=0;count=5?".$appid;
			}else if($type == "Zip_Code"){
				$url = $url ."/concordance/usps/".$location."?".$appid;
			}
			
			
			$xml = @simplexml_load_file(urlencode($url)/*,'SimpleXMLElement', LIBXML_NOWARNING*/);
			
			if($xml == NULL){
				echo "<root>NoResults</root>";
				return;
			}
			
			$woeid = array();
			$i = 0;
			
			
			if($xml->getName() == "places"){
				foreach($xml->children() as $child){
					foreach($child->children() as $element){
						if($element->getName() == "woeid"){
							$woeid[$i++] = $element;
							//echo $woeid[$i-1];
						}
					}
				}
			}
			
			if($xml->getName() == "concordance"){
				foreach($xml->children() as $child){
					if($child->getName() == "woeid"){
						$woeid[$i++] = $child;
						//echo $woeid[$i-1];
					}
				}
			}
			
			$weathers = array();
			
			if(sizeof($woeid) != 0){
				display($woeid);
			}else{
				echo "<root>NoResults</root>";
			}
?>

