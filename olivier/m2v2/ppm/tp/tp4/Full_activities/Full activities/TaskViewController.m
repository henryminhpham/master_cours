//
//  TaskViewController.m
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "TaskViewController.h"

@interface TaskViewController ()

@end

@implementation TaskViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        v = [[TaskView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        [self setView:v];
        navController = [super navigationController];
        UIBarButtonItem *photoButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCamera target:self action:@selector(addNewPhoto:)];
        [[self navigationItem] setRightBarButtonItem:photoButton];
        [v setFromOrientation:[[UIApplication sharedApplication] statusBarOrientation]];
    }
    return self;
}

- (void) addNewPhoto:(id)sender{
    imagePicker = [[UIImagePickerController alloc] init];
    [imagePicker setDelegate:self];
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        [imagePicker setSourceType:UIImagePickerControllerSourceTypeCamera];
        NSArray *m = [UIImagePickerController availableMediaTypesForSourceType:UIImagePickerControllerSourceTypeCamera];
        [imagePicker setMediaTypes:m];
    } else {
        [imagePicker setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    }
    [imagePicker setAllowsEditing:YES];
    [self presentViewController:imagePicker animated:YES completion:nil];
}

-(void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    [picker dismissViewControllerAnimated:YES completion:nil];
}

-(void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    [picker dismissViewControllerAnimated:YES completion:nil];
    NSString *mediaType = [info objectForKey:UIImagePickerControllerMediaType];
    if (CFStringCompare((CFStringRef) mediaType, kUTTypeImage, 0) == kCFCompareEqualTo) {
        UIImage *i = [info objectForKey:UIImagePickerControllerEditedImage];
        if (!i) {
            i = [info objectForKey:UIImagePickerControllerOriginalImage];
        }
        if (photo) {
            [photo removeFromSuperview];
            [photo release];
        }
        photo = [[UIImageView alloc] initWithImage:i];
        [photo setFrame:CGRectMake(20, 300, 150, 150)];
        [v addSubview:photo];
    }
}

- (void) changeCell:(CellContent*) c{
    [v setCell:c];
    [self setCell:c];
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
