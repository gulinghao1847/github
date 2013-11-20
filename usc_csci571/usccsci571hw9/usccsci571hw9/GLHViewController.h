//
//  GLHViewController.h
//  571hw9
//
//  Created by linghao_gu on 13-11-18.
//  Copyright (c) 2013年 linghao. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GLHViewController : UIViewController  <NSURLConnectionDataDelegate>

@property (weak, nonatomic) IBOutlet UITextField *location;

@property(nonatomic,assign) NSMutableData *receivedData; //<==== note use assign, not retain

//@property (weak, nonatomic) IBOutlet UITextView *textField;

@property (weak, nonatomic) IBOutlet UITextView *textField;

@property (weak, nonatomic) IBOutlet UITextField *validate;

@property (weak, nonatomic) IBOutlet UILabel *regionLabel;

@property (weak, nonatomic) IBOutlet UILabel *cityLabel;

@property (weak, nonatomic) IBOutlet UIImageView *tempImage;

@property (weak, nonatomic) IBOutlet UILabel *weatherLabel;

@property (weak, nonatomic) IBOutlet UILabel *tempLabel;

@end
