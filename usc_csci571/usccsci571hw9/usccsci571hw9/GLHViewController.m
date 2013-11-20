//
//  GLHViewController.m
//  571hw9
//
//  Created by linghao_gu on 13-11-18.
//  Copyright (c) 2013年 linghao. All rights reserved.
//

#import "GLHViewController.h"

@interface GLHViewController ()

@property (nonatomic, strong) NSMutableData   *buffer;
@property (nonatomic, strong) NSURLConnection *connection;

@end

@implementation GLHViewController

@synthesize location = _location;
NSString* location;
NSString* type;
NSString* tempUnit = @"F";
NSArray* jsonData;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)weatherSearch:(id)sender {
    location = self.location.text;
    NSInteger valid = [self validate:location];
    NSMutableString *url = [NSMutableString stringWithFormat:@"http://cs-server.usc.edu:22688/examples/servlet/weatherSearch?location=%@&type=%@&tempUnit=%@", location, type, tempUnit];
    if (valid) {
        [self makeRequest:url];
    }
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
        self.textField.text = @"Connection Failed";
    }
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    /* clear the connection & the buffer */
    self.connection = nil;
    self.buffer     = nil;
    
    self.textField.text = [error localizedDescription];
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
                NSDictionary* jsonData = [jsonDictionary objectForKey:@"weather"];
                [self parseJson:jsonData];
            }
            else
            {
                self.textField.text = [error localizedDescription];
            }
            
            /* stop animating &amp; re-enable the fetch button */
            
            /* clear the connection &amp; the buffer */
            self.connection = nil;
            self.buffer     = nil;
        });
        
    });
}

//parse jsonData and put value
-(void) parseJson:(NSDictionary*)jsonData{
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
    //NSLog(@"%@",imageURL);
    [self loadImageFromUrl:imageURL];
}

-(void) loadImageFromUrl:(NSString*)urlString{
    NSURL* url = [NSURL URLWithString:urlString];
    NSData *imageData = [NSData dataWithContentsOfURL:url];
    self.tempImage.image = [UIImage imageWithData:imageData];
    //self.tempImage.image = [UIImage imageWithContentsOfURL:url];
}
//end of communication
@end

