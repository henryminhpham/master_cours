#import "View.h"

@implementation View

const int DEFAULT_X = 20;
const int DEFAULT_Y = 20;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    dejaMod = NO;
    if (self) {
        x_origin = DEFAULT_X;
        y_origin = DEFAULT_Y;
        if ([[[UIDevice currentDevice] systemVersion] characterAtIndex:0] =='6') {
            isiOS6 = YES;
        } else {
            isiOS6 = NO;
        }
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            isIpad = NO;
        } else {
            isIpad = YES;
        }
        myFrame = frame;
        
        UIImageView *background = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"mininav-elements/fond-2048x2048.jpg"]];
        [self addSubview:background];
        
        width = myFrame.size.width;
        heigth = myFrame.size.height;
        homeURL = [[NSURL alloc] initWithString:@"http://google.com"];
        
        toolbar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, y_origin, width, 40)];
        
        if (isiOS6) {
            [toolbar setBarStyle:UIBarStyleBlackTranslucent];
        } else {
            bandeau = [[UIView alloc] init];
            [bandeau setBackgroundColor:[UIColor colorWithRed:1 green:1 blue:1 alpha:0.4]];
            [self addSubview:bandeau];
            [bandeau release];
            [toolbar setBarStyle:UIBarStyleDefault];
        }
        
        webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 40+y_origin, width, heigth)];
        [self addSubview:webView];
        
        home = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh target:self action:@selector(goHomePage)];
        setHome = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAction target:self action:@selector(setHome)];
        backButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRewind target:self action:@selector(boutonToolbar:)];
        forwardButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFastForward target:self action:@selector(boutonToolbar:)];
        loadButton = [[UIBarButtonItem alloc] initWithTitle:@"URL" style:UIBarButtonItemStylePlain target:self action:@selector(newURL)];
        
        UIBarButtonItem *smallSp = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:@selector(alloc)];
        [smallSp setWidth:20];
        
        UIBarButtonItem *varSp = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:@selector(alloc)];
        [toolbar setItems:[NSArray arrayWithObjects:home, varSp, backButton, smallSp, loadButton, smallSp, forwardButton, varSp, setHome, nil]];
        crtBtColor = [[backButton tintColor] retain];
        [backButton setTintColor:[UIColor grayColor]];
        [forwardButton setTintColor:[UIColor grayColor]];
        alertGoTo = [[UIAlertView alloc] initWithTitle:@"URL" message:@"Entrez l'URL à charger" delegate:self cancelButtonTitle:@"Annuler" otherButtonTitles:@"OK", nil];
        [alertGoTo setAlertViewStyle:UIAlertViewStylePlainTextInput];
        [alertGoTo setTag:1];
        alertSetHome = [[UIAlertView alloc] initWithTitle:@"Home" message:@"Entrez l'URL de votre nouvelle page d'accueil" delegate:self cancelButtonTitle:@"Annuler" otherButtonTitles:@"OK", nil];
        [alertSetHome setAlertViewStyle:UIAlertViewStylePlainTextInput];
        [alertSetHome setTag:2];
        action = [[UIActionSheet alloc] initWithTitle:@"Aller à la page d'accueil" delegate:self cancelButtonTitle:@"Non" destructiveButtonTitle:@"Oui" otherButtonTitles:nil];
        [webView setDelegate:self];
        [self addSubview:toolbar];
        [webView loadRequest:[NSURLRequest requestWithURL:homeURL]];
        [webView release];
        [background release];
        [toolbar release];
        [forwardButton release];
        [backButton release];
        [home release];
        [setHome release];
        [varSp release];
        [smallSp release];
        
    }
    return self;
}

-(void) setFromOrientation:(UIInterfaceOrientation) o{
    CGRect viewSize = [self bounds];
    x_origin = DEFAULT_X;
    y_origin = DEFAULT_Y;
    [toolbar setFrame:CGRectMake(0, y_origin, width, 40)];
    [webView setFrame:CGRectMake(0, 40+y_origin, width, heigth)];
    if (o == UIInterfaceOrientationLandscapeLeft || o == UIInterfaceOrientationLandscapeRight) {
        heigth = viewSize.size.width;
        width = viewSize.size.height;
    } else {
        width = viewSize.size.width;
        heigth = viewSize.size.height;
    }
}


-(void) webViewDidFinishLoad:(UIWebView *)wv{
    if (![webView canGoBack]) {
        [backButton setTintColor:[UIColor grayColor]];
    } else {
        [backButton setTintColor:crtBtColor];
    }
    if (! [webView canGoForward]) {
        [forwardButton setTintColor:[UIColor grayColor]];
    } else {
        [forwardButton setTintColor:crtBtColor];
    }
}

-(void) webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Erreur" message:[NSString stringWithFormat:@"%@", [error localizedDescription]] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alertView autorelease];
    [alertView show];
}

-(void) boutonToolbar:(UIBarButtonItem*)sender{
    if (sender == backButton) {
        [webView goBack];
    } else {
        [webView goForward];
    }
    [self setNeedsDisplay];
}


-(void) alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex{
    if ([alertView tag] == 1 && buttonIndex==1) {
        NSURL* ctrUrl = [NSURL URLWithString:[[alertView textFieldAtIndex:0] text]];
        NSURLRequest *r = [NSURLRequest requestWithURL:ctrUrl];
        [webView loadRequest:r];
    } else if (buttonIndex==1) {
        homeURL = [[NSURL alloc] initWithString:[[alertView textFieldAtIndex:0] text]];
    }
}

-(void) newURL {
    [alertGoTo show];
}

-(void) goHomePage {
    if (!isIpad) {
        [action showFromToolbar:toolbar];
    } else {
        [action showFromBarButtonItem:home animated:YES];
    }
}

-(void) setHome {
    [alertSetHome show];
}


-(void) actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (buttonIndex == 0) {
        NSURLRequest *req = [NSURLRequest requestWithURL:homeURL];
        [webView loadRequest:req];
    }
}



-(void) dealloc{
    [homeURL release];
    [super dealloc];
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
