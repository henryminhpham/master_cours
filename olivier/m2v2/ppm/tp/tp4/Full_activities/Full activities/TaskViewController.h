//
//  TaskViewController.h
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TaskView.h"
#import "CellContent.h"
#import <MobileCoreServices/UTCoreTypes.h>

@interface TaskViewController : UIViewController<UINavigationControllerDelegate,UIImagePickerControllerDelegate>{
    UINavigationController *navController;
    TaskView *v;
    UIImageView *photo;
    UIImagePickerController *imagePicker;
}

@property(nonatomic, assign, readwrite) CellContent *cell;

- (void) changeCell:(CellContent*) c;

@end
