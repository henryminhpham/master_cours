#import <UIKit/UIKit.h>

@interface View : UIView<UIScrollViewDelegate> {
    
    UIImageView *imageView;
    UIView *backgroundView;
    UIScrollView *resizableView;
    
    UIStepper *stepper;
    
    UILabel *width_label;
    UILabel *heigth_label;
    UILabel *photo_label;
    
    UISlider *widthSlider;
    UISlider *heigthSlider;
    
}

@property(nonatomic,assign) int heigth;
@property(nonatomic,assign) int width;
@property(nonatomic,assign) int x_axis;
@property(nonatomic,assign) int y_axis;
@property(nonatomic,assign) bool isIpad;

- (void) setFromOrientation:(UIInterfaceOrientation) o ;
@end

