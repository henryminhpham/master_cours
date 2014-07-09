#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreLocation/CLLocationManagerDelegate.h>
#import <MapKit/MapKit.h>
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>
#import <util.h>
#import <CoreGraphics/CoreGraphics.h>
#import "myCustomAnnotation.h"


@interface View : UIView <CLLocationManagerDelegate, MKMapViewDelegate, ABPeoplePickerNavigationControllerDelegate, ABNewPersonViewControllerDelegate, UINavigationControllerDelegate>{
    UIView *background;
    UIButton *contact, *remember,*forget;
    MKPointAnnotation *currentPoint;
    CLLocationManager *locManager;
    MKMapView *map;
    CGRect myframe;
    ABPeoplePickerNavigationController *abNavCont;
    ABNewPersonViewController *abNewPersCont;
    
    BOOL isIpad;
    int x_origin, y_origin, width, heigth, nbLieu, rapport;    
}

@property(assign,nonatomic)UIViewController *myViewCont;
-(void) setFromOrientation:(UIInterfaceOrientation) o;

@end
