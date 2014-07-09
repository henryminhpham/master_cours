//
//  TableViewController.m
//  The galaxy traveler guide
//
//  Created by m2sar on 09/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "TableViewController.h"
#import "PlanetViewController.h"
#import "AppDelegate.h"

BOOL tabAcces[20] = {YES, YES, NO, NO, YES, NO, YES, NO, NO, NO, YES, YES, NO, NO,
    YES, NO, NO, YES, NO, YES};

@interface TableViewController ()

@end

@implementation TableViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
      
        navController = [super navigationController];
        content = [[NSMutableArray alloc] init];
        [content addObject:[[NSMutableArray alloc] init]];
        int x;
        compteur = 1;
        
        NSArray *tabNom = [[NSArray alloc] initWithObjects:@"Tatooine",@"Yavin IV",@"Endor",@"Geonosis",@"Hoth",@"Coruscan",@"Alderaan",@"Bespin",@"Kamino",@"Mustafar",@"Dagobah",@"Dantooine",@"Bestine",@"Polus",@"Mon Calamari",@"Kuath",@"Sholah",@"Ryloth",@"Alzoc III",@"Jabin", nil];
        
        
        for (x=0; x<20; x++) {
          [[content objectAtIndex:0] addObject:[[CellContent alloc]
          initWithLabel:[tabNom objectAtIndex:x] andWithBool:tabAcces[x] andPlanetNumber:x ]];
        }
        
        
    }
    
    return self;
   
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{

    // Return the number of sections.
    return [content count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{

    // Return the number of rows in the section.
    return [[content objectAtIndex:section] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    NSInteger section = [indexPath section];
    NSInteger row = [indexPath row];
    [CellIdentifier autorelease];
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
    }
    [[cell textLabel] setText:[NSString stringWithFormat:@"%@",[[[content objectAtIndex:section] objectAtIndex:row] label]]];
    if ((isJedi && tabAcces[[indexPath indexAtPosition:1]])||(!isJedi && !tabAcces[[indexPath indexAtPosition:1]])) {
        [[cell detailTextLabel] setText:@"Has acces"];/*[NSString stringWithFormat:@"%@",[[[content objectAtIndex:section] objectAtIndex:row] hasAcces]]];*/
         }
         else {
             [[cell detailTextLabel] setText:@"Has not acces"];
         }
    NSString *owner;
    if (tabAcces[[indexPath indexAtPosition:1]]) {
        [[cell textLabel] setTextColor:[UIColor blueColor]];
        owner = @"leia";
    } else{
        owner = @"vador";
        [[cell textLabel] setTextColor:[UIColor redColor]];
    }
    [[cell imageView] setImage:[UIImage imageNamed:[NSString stringWithFormat:@"chatelet-elements/%@.png", owner]]];
    
    // Configure the cell...
    return cell;
}

-(void)viewDidAppear:(BOOL)animated{
    [[self tableView] reloadData];
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{

    if ((tabAcces[[indexPath indexAtPosition:1]] && isJedi) || (!tabAcces[[indexPath indexAtPosition:1]] && !isJedi)) {
        PlanetViewController *pvc = [[PlanetViewController alloc] initWithNum:[indexPath indexAtPosition:1]];
               
    [[self navigationController] pushViewController:pvc animated:YES];
    }
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a story board-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}

 */

@end
