//
//  ViewController.h
//  LocaliseMoi
//
//  Created by m2sar on 10/01/2014.
//  Copyright (c) 2014 m2sar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MapView.h"
#import "CellMapContent.h"

@interface MapViewController : UIViewController<UITextViewDelegate, NSURLConnectionDataDelegate, NSURLConnectionDelegate, NSXMLParserDelegate> {
    
    MapView* view;
    NSMutableData* webData;
    
    BOOL isLng, isLat;
    int isFirst;
    CellMapContent* mapContent;
}

- (void) makePosition: (CellMapContent*) mapContent;

- (CellMapContent*) getMapContent;

- (void) showNavigationButton:(UIBarButtonItem*)b;

- (void) hideNavigationButton;

@end
