//
//  forecastCell.h
//  usccsci571hw9
//
//  Created by linghao_gu on 13-11-20.
//  Copyright (c) 2013年 linghao. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface forecastCell : UICollectionViewCell
@property (weak, nonatomic) IBOutlet UILabel *dateLabel;
@property (weak, nonatomic) IBOutlet UILabel *weatherLabel;
@property (weak, nonatomic) IBOutlet UILabel *highLabel;
@property (weak, nonatomic) IBOutlet UILabel *lowLabel;

@end
