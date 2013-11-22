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

@end

@implementation GLHViewController

@synthesize location = _location;
NSString* location;
NSString* type;
NSString* tempUnitText;
NSDictionary* jsonData = nil;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSLog(@"HERE IN VIEWDIDLOAD");
    self.location.delegate = self;

    self.weatherForecast.delegate = self;
    self.weatherForecast.dataSource = self;
    
    //self.weatherForecast = nil;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)weatherSearch:(id)sender {
    location = self.location.text;
    NSInteger valid = [self validate:location];
    tempUnitText = [self.tempUnit titleForSegmentAtIndex:self.tempUnit.selectedSegmentIndex];
    NSLog(@"%@",tempUnitText);
    NSMutableString *url = [NSMutableString stringWithFormat:@"http://cs-server.usc.edu:22688/examples/servlet/weatherSearch?location=%@&type=%@&tempUnit=%@", location, type, tempUnitText];
    if (valid) {
        [self makeRequest:url];
    }
    
    //for collection view:
}

-(NSInteger)validate:(NSString*) myString{
    NSString* reg = @"^[0-9]*$";
    NSInteger result = [self regEx:reg regString:myString];
    if(result == 0){
        NSLog(@"City");
        type = @"City";
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
                NSLog(@"%@",[error localizedDescription]);
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
    NSString* temp = [NSString stringWithFormat:@"%@%@",
                      [[jsonData objectForKey:@"condition"] objectForKey:@"temp"],
                      [[jsonData objectForKey:@"units"] objectForKey:@"temperature"]
                      ];
    self.tempLabel.text = temp;
    
    //set collection view:
    //NSArray* forecast = [jsonData objectForKey:@"forecast"];
    //NSInteger num = [forecast count];
    //for(NSInteger idx = 0; idx < num; idx++){
        [self.weatherForecast reloadData];
    //}
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
- (IBAction)shareCurWeather:(id)sender {
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
        return cell;
    }
    NSArray* forecast = [jsonData objectForKey:@"forecast"];
    NSDictionary* dayWeather = [forecast objectAtIndex:indexPath.item];
    cell.dateLabel.text = [dayWeather objectForKey:@"day"];
    cell.weatherLabel.text = [dayWeather objectForKey:@"text"];
    cell.highLabel.text = [NSString stringWithFormat:@"%@",[dayWeather objectForKey:@"high"]];
    cell.lowLabel.text = [NSString stringWithFormat:@"%@",[dayWeather objectForKey:@"low"]];
    return cell;
}

//end of communication
@end

