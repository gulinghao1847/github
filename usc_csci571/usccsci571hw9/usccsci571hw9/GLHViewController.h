//
//  GLHViewController.h
//  571hw9
//
//  Created by linghao_gu on 13-11-18.
//  Copyright (c) 2013年 linghao. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <FacebookSDK/FacebookSDK.h>

@interface GLHViewController : UIViewController  <NSURLConnectionDataDelegate, FBLoginViewDelegate, UITextFieldDelegate,UICollectionViewDataSource, UICollectionViewDelegate>

//@property (weak, nonatomic) IBOutlet UITextField *location;
@property (weak, nonatomic) IBOutlet UITextField *location;

@property(nonatomic,assign) NSMutableData *receivedData; //<==== note use assign, not retain

@property (weak, nonatomic) IBOutlet UISegmentedControl *tempUnit;//f or c

@property (weak, nonatomic) IBOutlet UILabel *cityLabel;

@property (weak, nonatomic) IBOutlet UILabel *regionLabel;

@property (weak, nonatomic) IBOutlet UIImageView *tempImage;

@property (weak, nonatomic) IBOutlet UILabel *weatherLabel;

@property (weak, nonatomic) IBOutlet UILabel *tempLabel;

@property (weak, nonatomic) IBOutlet UIButton *shareCur;

//@property (weak, nonatomic) IBOutlet UIButton *shareFore;

@property (weak, nonatomic) IBOutlet UICollectionView *weatherForecast;

@property (weak, nonatomic) IBOutlet UIButton *shareWeatherForecast;

@end
