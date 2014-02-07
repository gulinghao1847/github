//
//  GLHViewController.m
//  571hw9
//
//  Created by linghao_gu on 13-11-18.
//  Copyright (c) 2013年 linghao. All rights reserved.
//

#import "GLHViewController.h"
#import "forecastCell.h"

@interface GLHViewController ()

@property (nonatomic, strong) NSMutableData   *buffer;
@property (nonatomic, strong) NSURLConnection *connection;
@property BOOL navigateAwayFromTab;

@end

@implementation GLHViewController

@synthesize location = _location;
NSString* locationText;
NSString* type;
NSString* tempUnitText;
NSDictionary* jsonData = nil;
NSInteger postInformationToWall;
bool questionAnswered = FALSE;
NSCondition *condition;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSLog(@"HERE IN VIEWDIDLOAD");
    self.location.delegate = self;

    self.weatherForecast.delegate = self;
    self.weatherForecast.dataSource = self;
    
    //self.weatherForecast = nil;
    
    //self.view.backgroundColor = [[UIColor alloc] initWithPatternImage:[UIImage imageNamed:@"sky.jpg"]];
    UIImage* _backGround = [UIImage imageNamed:@"sky.jpg"];
    UIImageView* _backGroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    _backGroundView.frame = self.view.frame;
    
    [self.view addSubview:_backGroundView];
    [self.view sendSubviewToBack:_backGroundView];
    
    self.cityLabel.textColor = [UIColor whiteColor];
    self.regionLabel.textColor = [UIColor whiteColor];
    self.weatherLabel.textColor = [UIColor whiteColor];
    self.tempLabel.textColor = [UIColor whiteColor];
    self.forecastLable.textColor = [UIColor whiteColor];
    self.wrongWeather.textColor = [UIColor whiteColor];

    self.DateLabelText.textColor = [UIColor whiteColor];
    self.weatherLabelText.textColor = [UIColor whiteColor];
    self.HighLabelText.textColor = [UIColor whiteColor];
    self.lowLabelText.textColor = [UIColor whiteColor];
    
    
    self.wrongWeather.numberOfLines = 2;
    self.weatherLabel.numberOfLines = 2;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)weatherSearch:(id)sender {
    locationText = self.location.text;
    NSInteger valid = [self validate:locationText];
    tempUnitText = [self.tempUnit titleForSegmentAtIndex:self.tempUnit.selectedSegmentIndex];
    NSLog(@"%@",tempUnitText);
    //NSString* urlEncodingLocation = [locationText stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    locationText = [locationText stringByReplacingOccurrencesOfString:@"," withString:@"%2C"];
    locationText = [locationText stringByReplacingOccurrencesOfString:@" " withString:@"+"];
    locationText = [locationText stringByReplacingOccurrencesOfString:@"'" withString:@""];
    NSMutableString *url = [NSMutableString stringWithFormat:@"http://cs-server.usc.edu:22688/examples/servlet/weatherSearch?location=%@&type=%@&tempUnit=%@",
                            locationText,
                            type,
                            tempUnitText];
    NSLog(@"%@",url);
    if (valid) {
        [self makeRequest:url];
    }
    
    //for collection view:
}

-(NSInteger)validate:(NSString*) myString{
    if ([myString isEqualToString:@""]) {
        [self showAlert:@"Input Is Empty!!"];
        return 0;
    }
    NSString* reg = @"^[0-9]*$";
    NSInteger result = [self regEx:reg regString:myString];
    if(result == 0){
        NSLog(@"City");
        NSString* test = @"^[.a-zA-Z0-9 -]+,$";
        NSInteger test1 = [self regEx:test regString:myString];
        NSLog(@"%d",test1);
        NSString* reg1 = @"^['.a-zA-Z0-9 -]+,['.a-zA-Z0-9 -]+$";
        NSString* reg2 = @"^['.a-zA-Z0-9 -]+,['.a-zA-Z0-9 -]+,['.a-zA-Z0-9 -]+$";
        NSInteger r1 = [self regEx:reg1 regString:myString];
        NSInteger r2 = [self regEx:reg2 regString:myString];
        NSLog(@"%d     %d",r1,r2);
        if(r1 == 0 && r2 == 0){
            [self showAlert:@"City Name should like the following format\nLos Angeles,CA"];
            return 0;
        }else{
            type = @"city";
        }
    }else{
        NSLog(@"Zip_Code");
        //ALL VALUES ARE NUMBERS
        reg = @"^[0-9]{5}$";
        result = [self regEx:reg regString:myString];
        if(result == 0){
            [self showAlert:@"Zip Code number should be exactly 5 digits\n For example: 90007"];
            return 0;
        }else{
            type = @"Zip_Code";
        }
    }
    return 1;
}


//communiate with th/Users/linghao/Desktop/571hw9/571hw9/GLHViewController.he servlets
-(void)makeRequest:(NSString*) url{
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:url]];
    
    /* create the connection */
    self.connection = [NSURLConnection connectionWithRequest:request delegate:self];
    
    /* ensure the connection was created */
    if (self.connection)
    {
        /* initialize the buffer */
        self.buffer = [NSMutableData data];
        
        /* start the request */
        [self.connection start];
    }
    else
    {
        NSLog(@"Connection Failed");
    }
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    /* clear the connection & the buffer */
    self.connection = nil;
    self.buffer     = nil;
    
    NSLog(@"%@",[error localizedDescription]);
    NSLog(@"Connection failed! Error - %@ %@",
          [error localizedDescription],
          [[error userInfo] objectForKey:NSURLErrorFailingURLStringErrorKey]);
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    /* reset the buffer length each time this is called */
    [self.buffer setLength:0];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    /* Append data to the buffer */
    [self.buffer appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    /* dispatch off the main queue for json processing */
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        
        NSError *error = nil;
        NSDictionary *jsonDictionary = [NSJSONSerialization JSONObjectWithData:_buffer options:0 error:&error];
        
        /* dispatch back to the main queue for UI */
        dispatch_async(dispatch_get_main_queue(), ^{
            
            /* check for a JSON error */
            if (!error)
            {
                jsonData = [jsonDictionary objectForKey:@"weather"];
                [self parseJson];
            }
            else
            {
                NSLog(@"in connection%@",[error localizedDescription]);
                [self clearAllLable];
                [self.weatherForecast reloadData];
                jsonData = nil;
                self.wrongWeather.text = @"Weather Information \ncan't be found!";
                [self setTableLabel:1];
            }
            
            /* stop animating &amp; re-enable the fetch button */
            
            /* clear the connection &amp; the buffer */
            self.connection = nil;
            self.buffer     = nil;
        });
        
    });
}

//parse jsonData and put value
-(void) parseJson{
    //
    self.wrongWeather.text = @"";
    NSDictionary* location = [jsonData objectForKey:@"location"];
    NSString* cityText = [location objectForKey:@"city"];
    NSString* region = [location objectForKey:@"region"];
    NSString* country = [location objectForKey:@"country"];
    
    NSLog(@"%@",cityText);
    self.cityLabel.text = cityText;
    NSString* regionText = [NSString stringWithFormat:@"%@, %@",region, country];
    self.regionLabel.text = regionText;
    //set the weather picture
    NSString* imageURL = [jsonData objectForKey:@"img"];
    [self loadImageFromUrl:imageURL];
    
    //set the weather information
    NSString* weather = [[jsonData objectForKey:@"condition"] objectForKey:@"text"];
    self.weatherLabel.text = weather;
    
    //set the temperature information
    NSString* temp = [NSString stringWithFormat:@"%@°%@",
                      [[jsonData objectForKey:@"condition"] objectForKey:@"temp"],
                      [[jsonData objectForKey:@"units"] objectForKey:@"temperature"]
                      ];
    self.tempLabel.text = temp;
    
    //set collection view:
    [self.weatherForecast reloadData];
    
    //
    //self.forecastLable.text = @"Forecast";
    [self setTableLabel:0];
}

-(void) loadImageFromUrl:(NSString*)urlString{
    NSURL* url = [NSURL URLWithString:urlString];
    NSData *imageData = [NSData dataWithContentsOfURL:url];
    self.tempImage.image = [UIImage imageWithData:imageData];
    //self.tempImage.image = [UIImage imageWithContentsOfURL:url];
}


- (NSDictionary*)parseURLParams:(NSString *)query {
    NSArray *pairs = [query componentsSeparatedByString:@"&"];
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    for (NSString *pair in pairs) {
        NSArray *kv = [pair componentsSeparatedByString:@"="];
        NSString *val =
        [kv[1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        params[kv[0]] = val;
    }
    return params;
}

-(NSString*)getFinalString:(NSString*)org{
    return org != nil ? org : @" ";
}

-(NSString*)addCommasString:(NSString*)org{
    NSString* newString = [self getFinalString:org];
    
    if([newString isEqualToString:@" "]){
        return org;
    }else{
        return [NSString stringWithFormat:@"%@,",newString];
    }
}
- (IBAction)shareCurrentWeather:(id)sender {
    NSDictionary* location = [jsonData objectForKey:@"location"];
    NSString* city = [self addCommasString:[location objectForKey:@"city"]];
    NSString* region = [self addCommasString:[location objectForKey:@"region"]];
    NSString* country = [self getFinalString:[location objectForKey:@"country"]];
    
    NSString* area = [NSString stringWithFormat:@"%@%@%@",city, region, country];
    
    NSString* weather = [self getFinalString:[[jsonData objectForKey:@"condition"]
                                              objectForKey:@"text"]];
    
    NSString* temperature = [self getFinalString:[[jsonData objectForKey:@"condition"]
                                                  objectForKey:@"temp"]];
    
    NSString* img = [[jsonData objectForKey:@"img"]stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    NSString* feed = [[jsonData objectForKey:@"feed"]stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    NSString* link = [[jsonData objectForKey:@"link"]stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    NSString* caption = [NSString stringWithFormat:@"The current condition for %@ is %@", [self getFinalString:[location objectForKey:@"city"]], weather];
    NSString* description = [NSString stringWithFormat:@"Temperature is %@%@", temperature,tempUnitText];
    NSString* properties = [NSString stringWithFormat:@"{\"Look at details \":{\"href\":\"%@\",\"text\":\"here\"}}",link];
    
    NSMutableDictionary *params =
    [NSMutableDictionary dictionaryWithObjectsAndKeys:
     area, @"name",
     caption, @"caption",
     description, @"description",
     feed, @"link",
     img, @"picture",
     properties,@"properties",
     nil];
    [self postToWall:params];
}

- (IBAction)shareWeaFore:(id)sender {

    NSDictionary* location = [jsonData objectForKey:@"location"];
    NSString* city = [self addCommasString:[location objectForKey:@"city"]];
    NSString* region = [self addCommasString:[location objectForKey:@"region"]];
    NSString* country = [self getFinalString:[location objectForKey:@"country"]];
    
    NSString* area = [NSString stringWithFormat:@"%@%@%@",city, region, country];
    
    NSString* weather = [self getFinalString:[[jsonData objectForKey:@"condition"]
                                              objectForKey:@"text"]];
    
    NSString* temperature = [self getFinalString:[[jsonData objectForKey:@"condition"]
                                                  objectForKey:@"temp"]];
    
    NSString* img = @"http://cs-server.usc.edu:22688/examples/servlets/forecast.jpg";
    NSString* feed = [[jsonData objectForKey:@"feed"]stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    NSString* link = [[jsonData objectForKey:@"link"]stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSString* caption = [NSString stringWithFormat:@"Weather Forecast for %@", [self getFinalString:[location objectForKey:@"city"]]];
    NSString* properties = [NSString stringWithFormat:@"{\"Look at details \":{\"href\":\"%@\",\"text\":\"here\"}}",link];
    NSMutableString* description = [NSMutableString string];
    
    NSArray* forecast = [jsonData objectForKey:@"forecast"];
    NSLog(@"Count: !!!!%d",[forecast count]);
    for (NSInteger idx = 0; idx < [forecast count]; idx++) {
        NSDictionary* everydayForecast = [forecast objectAtIndex:idx];
        [description appendFormat:@"%@: %@, %@/%@", [everydayForecast objectForKey:@"day"],
         [everydayForecast objectForKey:@"text"],
         [self getTemperature:[everydayForecast objectForKey:@"high"]],
         [self getTemperature:[everydayForecast objectForKey:@"low"]]
         ];
        if(idx == [forecast count] - 1){
            [description appendFormat:@"."];
        }else{
            [description appendFormat:@";"];
        }
    }
    NSLog(@"%@",description);
    
    NSMutableDictionary *params =
    [NSMutableDictionary dictionaryWithObjectsAndKeys:
     area, @"name",
     caption, @"caption",
     description, @"description",
     feed, @"link",
     img, @"picture",
     properties,@"properties",
     nil];
    [self postToWall:params];
}

-(NSString*)getTemperature:(NSString*)temp
{
    return temp;
}


- (void)postToWall:(NSMutableDictionary*) params {
    [FBWebDialogs presentFeedDialogModallyWithSession:nil
                                           parameters:params
                                              handler:
     ^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
         if (error) {
             // Error launching the dialog or publishing a story.
             NSLog(@"Error publishing story.");
         } else {
             if (result == FBWebDialogResultDialogNotCompleted) {
                 // User clicked the "x" icon
                 NSLog(@"User canceled story publishing.");
             } else {
                 // Handle the publish feed callback
                 NSDictionary *urlParams = [self parseURLParams:[resultURL query]];
                 if (![urlParams valueForKey:@"post_id"]) {
                     // User clicked the Cancel button
                     NSLog(@"User canceled story publishing.");
                 } else {
                     // User clicked the Share button
                     NSString *msg = [NSString stringWithFormat:
                                      @"Posted story, id: %@",
                                      [urlParams valueForKey:@"post_id"]];
                     NSLog(@"%@", msg);
                     // Show the result in an alert
                     [[[UIAlertView alloc] initWithTitle:@"Result"
                                                 message:msg
                                                delegate:nil
                                       cancelButtonTitle:@"OK!"
                                       otherButtonTitles:nil]
                      show];
                 }
             }
         }
     }];
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField {
    NSLog(@"here");
    [textField resignFirstResponder];
    return YES;
}

//collection view part

-(NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    return 1;
}

-(NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    NSArray* forecast = [jsonData objectForKey:@"forecast"];
    NSInteger a = [forecast count];
    NSLog(@"%d", a);
    NSLog(@"%@",forecast);
    return a;
}

-(UICollectionViewCell*)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString* cellIdentifier = @"Cell";
    forecastCell* cell = [collectionView dequeueReusableCellWithReuseIdentifier:cellIdentifier forIndexPath:indexPath];
    if (jsonData == nil) {
        cell.dateLabel.text = @"";
        cell.weatherLabel.text = @"";
        cell.highLabel.text = @"";
        cell.lowLabel.text = @"";
        //self.forecastLable.text = @"";
        return cell;
    }
    
    NSArray* forecast = [jsonData objectForKey:@"forecast"];
    NSDictionary* dayWeather = [forecast objectAtIndex:indexPath.item];
    cell.dateLabel.text = [dayWeather objectForKey:@"day"];
    cell.dateLabel.textColor = [UIColor whiteColor];
    cell.weatherLabel.text = [dayWeather objectForKey:@"text"];
    cell.weatherLabel.textColor = [UIColor whiteColor];
    cell.weatherLabel.lineBreakMode = UILineBreakModeCharacterWrap;
    cell.weatherLabel.numberOfLines = 3;
    cell.highLabel.text = [self showTemperature: [dayWeather objectForKey:@"high"]];//[dayWeather objectForKey:@"high"]];
    cell.highLabel.textColor = [UIColor whiteColor];
    cell.lowLabel.text = [self showTemperature: [dayWeather objectForKey:@"low"]];
    cell.lowLabel.textColor = [UIColor whiteColor];
    return cell;
}

-(void)showAlert:(NSString*) alterString{
    UIAlertView *alert = [[UIAlertView alloc]
                          initWithTitle: @"Announcement"
                          message: alterString
                          delegate: nil
                          cancelButtonTitle:@"OK"
                          otherButtonTitles:nil];
    [alert show];
}

-(NSInteger)regEx:(NSString*) pattern regString:(NSString*) myString{
    NSError *error = NULL;
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:pattern
                                                                           options:NSRegularExpressionCaseInsensitive
                                                                             error:&error];
    NSUInteger numberOfMatches = [regex numberOfMatchesInString:myString
                                                        options:0
                                                          range:NSMakeRange(0, [myString length])];
    return numberOfMatches;
}

-(NSString*)showTemperature:(NSString*) temp{
    NSString* newTemp = [NSString stringWithFormat:@"%@°%@",temp,tempUnitText];
    return newTemp;
}

-(void)clearAllLable{
    self.cityLabel.text = @"";
    self.regionLabel.text = @"";
    self.tempImage.image = nil;
    self.weatherLabel.text = @"";
    self.tempLabel.text = @"";
    self.wrongWeather.text = @"";
}

-(void)setTableLabel:(NSInteger)isClear{
    if(isClear == 1)//clear the label
    {
        self.forecastLable.text = @"";
        self.DateLabelText.text = @"";
        self.weatherLabelText.text = @"";
        self.HighLabelText.text = @"";
        self.lowLabelText.text = @"";
    }else{
        self.forecastLable.text = @"Forecast";
        self.DateLabelText.text = @"Date";
        self.weatherLabelText.text = @"Weather";
        self.HighLabelText.text = @"High";
        self.lowLabelText.text = @"Low";
    }
}



//end of communication
@end

