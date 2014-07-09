//
//  TableViewController.m
//  Full activities
//
//  Created by m2sar on 12/12/2013.
//  Copyright (c) 2013 m2sar. All rights reserved.
//

#import "TableViewController.h"
#import "TaskViewController.h"

@interface TableViewController ()

@end

@implementation TableViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        
        content = [[NSMutableArray alloc] init];
        [content addObject:[[NSMutableArray alloc] init]];
        [[content objectAtIndex:0] addObject:[[CellContent alloc] initWithLabel:@"tache 1" andWithDetail:@"pas de détail" andWithPrio:0]];
        [content addObject:[[NSMutableArray alloc] init]];
        [[content objectAtIndex:1] addObject:[[CellContent alloc] initWithLabel:@"tache 1" andWithDetail:@"pas de détail" andWithPrio:0]];
        [content retain];
        [[self navigationItem] setLeftBarButtonItem:[self editButtonItem]];
        UIBarButtonItem *addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(addNewItem)];
        [[self navigationItem] setRightBarButtonItem:addButton];
        
    }
    return self;
}

-(void) addNewItem {
    [[content objectAtIndex:0] insertObject:[[CellContent alloc]
                                             initWithLabel:@"Nouvelle Tache" andWithDetail:[NSString stringWithFormat:@"Current priority %d",0] andWithPrio:0] atIndex:0];
    [[self tableView] reloadData];
}


- (void)viewDidLoad
{
    
    [super viewDidLoad];
    [[self tableView] reloadData];
    /*[[self navigationItem] setTitle:@"TODO List"];
    
    [[self navigationItem] setLeftBarButtonItem:[self editButtonItem]];
    UIBarButtonItem *addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(addNewItem)];
    [[self navigationItem] setRightBarButtonItem:addButton];*/
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
    return [content count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [[content objectAtIndex:section] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier=@"Cell";
    
    NSInteger section = [indexPath section];
    NSInteger row = [indexPath row];
    [CellIdentifier autorelease];
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
        }
    [[cell textLabel] setText:[NSString stringWithFormat:@"%@",[[[content objectAtIndex:section] objectAtIndex:row] label]]];
    [[cell detailTextLabel] setText:[NSString stringWithFormat:@"%@",[[[content objectAtIndex:section] objectAtIndex:row] detail]]];
    UIImage * img = [[[content objectAtIndex:section] objectAtIndex:row] pastille];
    [[cell imageView] setImage:img];
    return cell;
}
    
    // Configure the cell...
    



// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}



// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSInteger theSection = [indexPath section];
    NSInteger theRow = [indexPath row];
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [[content objectAtIndex:theSection] removeObjectAtIndex:theRow];
        
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        static NSString *CellIdentifier = @"Cell";
        
        NSInteger section = [indexPath section];
        NSInteger row = [indexPath row];
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
        if (cell == nil) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
        }
        [[cell textLabel] setText:[NSString stringWithFormat:@"%@",[[[content objectAtIndex:section] objectAtIndex:row] label]]];
        [[cell detailTextLabel] setText:[NSString stringWithFormat:@"%@",[[[content objectAtIndex:section] objectAtIndex:row] detail]]];
        
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
        [[content objectAtIndex:theSection] insertObject:cell atIndex:theRow];
        
        [tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
}

-(void)viewDidAppear:(BOOL)animated{
    [[self tableView] reloadData];
    NSLog(@"tata");
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    TaskViewController *tvc = [[TaskViewController alloc] initWithNibName:[super nibName] bundle:[super nibBundle]];
    
    [tvc changeCell:[[content objectAtIndex:[indexPath row]] objectAtIndex:0]];
    [[self navigationController] pushViewController:tvc animated:YES];
}


// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
    NSInteger fromSection = [fromIndexPath section];
    NSInteger fromRow = [fromIndexPath row];
    NSInteger toSection = [toIndexPath section];
    NSInteger toRow = [toIndexPath row];
    
    CellContent *crtContent = [[[content objectAtIndex:fromSection] objectAtIndex:fromRow] retain];
    [[content objectAtIndex:fromSection] removeObjectAtIndex:fromRow];
    [[content objectAtIndex:toSection] insertObject:crtContent atIndex:toRow];
    
    [[self tableView] reloadData];
}



// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}


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
