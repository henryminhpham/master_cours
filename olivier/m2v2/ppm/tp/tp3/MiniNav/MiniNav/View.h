#import <UIKit/UIKit.h>

@interface View : UIView <UIWebViewDelegate,UIAlertViewDelegate,UIActionSheetDelegate> {
    UIView *bandeau;
    UIWebView *webView;
    
    CGRect myFrame;
    BOOL isiOS6, isIpad, dejaMod;
    
    UIBarButtonItem *backButton, *forwardButton;
    UIBarButtonItem *home, *setHome, *loadButton;
    
    UIToolbar *toolbar;
    
    UIColor *crtBtColor;
    NSURL *homeURL;
    
    UIAlertView *alertGoTo, *alertSetHome;
    
    UIActionSheet *action;
    
    int width, heigth, x_origin, y_origin;
}

-(void) setFromOrientation:(UIInterfaceOrientation) o;

@end
